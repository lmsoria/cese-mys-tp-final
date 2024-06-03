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
#include "aes_128_encoder.h"
#include "xil_io.h"

#include "main.h"
#include "uart.h"

// === Macros definitions ========================================================================================== //

#define CHAR_ENTER   (0x0D)  // Used to detect a new line
#define CHAR_ESCAPE  (0x1B)  // Used to change the key
#define CLEAR_SCREEN ("\033[2J\033[H") // ASCII sequence to clear screen and go to HOME position

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

static void reset_key(void);
static void print_bar(void);
static void on_error(void);
static void on_getting_key(void);
static void on_setting_key(void);
static void on_echoing(void);

// === Public variable definitions ================================================================================= //
// === Private variable definitions ================================================================================ //

static uint8_t key_buffer[16] = {0};

static ApplicationState current_state;

// === Private function implementation ============================================================================= //

static void reset_key(void) { memset(key_buffer, 0, 16); }

static void print_bar(void) { xil_printf("--------------------------------------------------------------------------------\n\r"); }

static void on_error(void) { while(1); }

static void on_getting_key(void)
{
	static uint8_t show_message = 1;
	static uint8_t index = 0;
	uint8_t received_char = 0;

	// Ensure we print this message only once, during the entry.
	if(show_message) {
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
		key_buffer[index++] = received_char;

		if(index == 16) {
			goto exit_getting_key_state;
		}
	}

	// Echo the character back
	uart_write_byte(UART_SHELL, received_char);
	return;

	// State exit point. Reset internal variables
	exit_getting_key_state:
		current_state = SETTING_KEY;
		index = 0;
		show_message = 1;
		return;
}

static void on_setting_key(void)
{
	uart_write_bytes(UART_SHELL, (uint8_t*)"\n\r", 2);

	xil_printf("Using key: %s ( ", key_buffer);
	for(uint8_t i = 0; i < 16; i++) {
		xil_printf("%02x ", key_buffer[i]);
	}
	xil_printf(")\n\r");

	xil_printf("Started echo service on UART1. \n\r");
	xil_printf("Messages typed here will be sent encrypted using the specified key.\n\r");
	xil_printf("Press ESC to set a new key.\n\r");
	print_bar();

	current_state = ECHOING;
}

static void on_echoing(void)
{
	uint8_t received_char = uart_read_byte(UART_SHELL);

	// If user hits ESC, then clear screen and go back to GETTING_KEY state.
	if (CHAR_ESCAPE == received_char) {
		current_state = GETTING_KEY;
		reset_key();
		xil_printf(CLEAR_SCREEN);
		return;
	}

	// Echo the character back
	uart_write_byte(UART_SHELL, received_char);
	uart_write_byte(UART_CRYPTO, received_char);
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

	print_bar();
	xil_printf("AES-128 Encoder application starts here\n\r");
	print_bar();

	current_state = GETTING_KEY;

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

	print_bar();
	xil_printf("AES-128 Encoder application stopped\n\r");
	print_bar();

	return XST_SUCCESS;
}

// === End of documentation ======================================================================================== //
