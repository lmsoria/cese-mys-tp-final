/**********************************************************************************************************************
Copyright (c) 2024, Leandro Soria <leandromsoria@gmail.com>

Some fancy copyright message here (if needed)
**********************************************************************************************************************/

///
/// @file main.c
/// @brief Main application source file
///

// === Headers files inclusions ==================================================================================== //

#include <stdint.h>
#include "xil_io.h"
#include "xstatus.h"

#include "encoder.h"
#include "main.h"
#include "uart.h"

// === Macros definitions ========================================================================================== //

#define CHAR_ENTER   (0x0D)  // Used to detect a new line
#define CHAR_ESCAPE  (0x1B)  // Used to change the key
#define CLEAR_SCREEN ("\033[2J\033[H") // ANSI sequence to clear screen and go to HOME position

#define TERMINAL_SIZE_X (80U)
#define KEY_SIZE (16U)

// === Private data type declarations ============================================================================== //

/// @brief States that the main application can be
typedef enum {
	GETTING_KEY, ///< Getting the AES key from the user
	SETTING_KEY, ///< Setting the AES key to the encoder
	ECHOING,     ///< Sendinc encrypted data over UART1
	ERROR,       ///< An error happened. Halt.
} ApplicationState;

// === Private variable declarations =============================================================================== //
// === Private function declarations =============================================================================== //

/// @brief Reset the application key to be all zeroes. This function won't impact on the encoder stored key.
static void reset_key(void);

/// @brief Helper function to print a dashed line on terminal
static void print_bar(void);

/// @brief GETTING_KEY state entry point.
static void on_getting_key(void);

/// @brief SETTING_KEY state entry point.
static void on_setting_key(void);

/// @brief ECHOING state entry point.
static void on_echoing(void);

/// @brief ERROR state entry point.
static void on_error(void);

// === Public variable definitions ================================================================================= //
// === Private variable definitions ================================================================================ //

static uint8_t app_key[KEY_SIZE] = {0};

static ApplicationState current_state;

// === Private function implementation ============================================================================= //

static void reset_key(void) { memset(app_key, 0, KEY_SIZE); }

static void print_bar(void) { xil_printf("-------------------------------------------------------------------------------\n\r"); }

static void on_error(void) { while(1); }

static void on_getting_key(void)
{
	static uint8_t show_message = 1;
	static uint8_t index = 0;
	uint8_t received_char = 0;

	// Ensure we print this message only once, during the entry.
	if(show_message) {
		print_bar();
		xil_printf("AES-128 Encoder application starts here\n\r");
		print_bar();
		xil_printf("Enter the AES-128 Key: ");
		show_message = 0;
	}

	received_char = uart_read_byte(UART_SHELL);

	// Yes, it's horrible to use goto statements but an exception to the rule is to
	// create a single exit point. This is useful for state machines.
	// (or well, use C++ and create an State::exit() method instead)
	if (CHAR_ENTER == received_char) {
		goto exit_getting_key_state;
	} else {
		app_key[index++] = received_char;

		if(index == KEY_SIZE) {
			// Don't forget to echo the character back before we leave
			uart_write_byte(UART_SHELL, received_char);
			goto exit_getting_key_state;
		}
	}

	// Echo the character back
	uart_write_byte(UART_SHELL, received_char);
	return;

	// State exit point. Reset internal variables
	exit_getting_key_state:
	{
		current_state = SETTING_KEY;
		index = 0;
		show_message = 1;
		return;
	}
}

static void on_setting_key(void)
{
	uart_write_bytes(UART_SHELL, (uint8_t*)"\n\r", 2);

	xil_printf("Using key: %s ( ", app_key);
	for(uint8_t i = 0; i < KEY_SIZE; i++) {
		xil_printf("%02x ", app_key[i]);
	}
	xil_printf(")\n\r");

	encoder_set_key(app_key);

	xil_printf("Started echo service on UART1.\n\r");
	xil_printf("Messages typed here will be sent encrypted using the specified key.\n\r");
	xil_printf("Press ESC to set a new key.\n\r");
	print_bar();

	current_state = ECHOING;
}

static void on_echoing(void)
{
	// Variables used for debugging purposes, so we can show the processed data.
	const uint32_t* const KEY = encoder_get_key();
	const uint32_t* const PLAIN_TEXT = encoder_get_plain_text();
	const uint32_t* const CIPHER_TEXT = encoder_get_cipher_text();

	// Static variables to keep track of the cursor (for echo on the shell terminal)
	static uint32_t cursor_x = 0;
	static uint32_t cursor_y = 0;

	uint8_t plain_text_data[16] = {0};
	uint8_t cipher_text_data[16] = {0};

	// First step: Read user input.
	uint8_t received_char = uart_read_byte(UART_SHELL);

	// If user hits ESC, then clear screen and go back to GETTING_KEY state.
	if (CHAR_ESCAPE == received_char) {
		current_state = GETTING_KEY;
		reset_key();
		xil_printf(CLEAR_SCREEN);
		cursor_x = 0;
		cursor_y = 0;
		return;
	}

	// Second step: Encode the data.
	plain_text_data[0] = received_char;
	encoder_encode_data(plain_text_data, cipher_text_data);

    // Save current cursor position
    if (++cursor_x >= TERMINAL_SIZE_X || CHAR_ENTER == received_char) {
        cursor_x = 0;
        cursor_y++;
    }

	xil_printf("\033[11;1H");
    xil_printf("Key        : %08x %08x %08x %08x\n\r", KEY[0], KEY[1], KEY[2], KEY[3]);
	xil_printf("Plain Text : %08x %08x %08x %08x\n\r", PLAIN_TEXT[0], PLAIN_TEXT[1], PLAIN_TEXT[2], PLAIN_TEXT[3]);
    xil_printf("Cipher Text: %08x %08x %08x %08x\n\r", CIPHER_TEXT[0], CIPHER_TEXT[1], CIPHER_TEXT[2], CIPHER_TEXT[3]);
    xil_printf("\n\r");
    print_bar();

    // Move the cursor to the last position of typed text and echo the character back
    xil_printf("\033[%d;%dH%c", 16 + cursor_y, cursor_x, received_char);

    // Third step: Send cipher text (16 bytes) over UART1
	uart_write_bytes(UART_CRYPTO, cipher_text_data, 16);
}

// === Public function implementation ============================================================================== //

int main(void)
{
	if (uart_initialize(UART_CRYPTO, UART_CRYPTO_INSTANCE) == XST_FAILURE) {
		xil_printf("UART Crypto Initialization Failed\n\r");
		return XST_FAILURE;
	}

	if (uart_initialize(UART_SHELL, UART_SHELL_INSTANCE) == XST_FAILURE) {
		xil_printf("UART Shell Initialization Failed\n\r");
		return XST_FAILURE;
	}

	encoder_initialize(AES_INSTANCE);

	current_state = GETTING_KEY;

	xil_printf(CLEAR_SCREEN);

	while(1) {
		switch (current_state)
		{
		case GETTING_KEY:
			on_getting_key();
			break;
		case SETTING_KEY:
			on_setting_key();
			break;
		case ECHOING:
			on_echoing();
			break;
		case ERROR:
			on_error();
			break;
		default:
			on_error();
			break;
		}
	}

	// Should never reach here.
	return XST_SUCCESS;
}

// === End of documentation ======================================================================================== //
