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

#define CHAR_ENTER		0x0D	/* 'ESC' character is used as terminator */
#define CHAR_ESCAPE		0x1B	/* 'ESC' character is used as terminator */

// === Private data type declarations ============================================================================== //

typedef enum {
	GETTING_KEY,
	SETTING_KEY,
	ECHOING,
	ERROR,
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

static void print_bar(void) { xil_printf("----------------------------------------\r\n"); }

static void on_error(void) { while(1); }

static void on_getting_key(void)
{
	static uint8_t show_message = 1;
	static uint8_t index = 0;
	uint8_t received_char = 0;

	if(show_message) {
		xil_printf("Enter the AES-128 Key: ");
		show_message = 0;
	}

	received_char = uart_read_byte(UART_SHELL);
	if (CHAR_ENTER == received_char) {
		current_state = SETTING_KEY;
		index = 0;
		show_message = 1;
		return;

	} else {
		key_buffer[index++] = received_char;

		if(index == 16) {
			current_state = SETTING_KEY;
			index = 0;
			show_message = 1;
			return;
		}
	}

	// Echo the character back
	uart_write_byte(UART_SHELL, received_char);
}

static void on_setting_key(void)
{
	uart_write_bytes(UART_SHELL, (uint8_t*)"\r\n", 2);

	xil_printf("Setting key: %s ( ", key_buffer);
	for(uint8_t i = 0; i < 16; i++) {
		xil_printf("%02x ", key_buffer[i]);
	}
	xil_printf(")\r\n");

	xil_printf("Started echo service on UART1. \r\n");
	xil_printf("Messages typed here will be sent encrypted using the specified key.\r\n");
	print_bar();

	current_state = ECHOING;
}

static void on_echoing(void)
{
	uint8_t received_char = uart_read_byte(UART_SHELL);
	if (CHAR_ESCAPE == received_char) {
		current_state = GETTING_KEY;
		reset_key();
		xil_printf("\033[2J\033[H");
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
		xil_printf("UART Crypto Initialization Failed\r\n");
		return XST_FAILURE;
	}

	if (uart_initialize(UART_SHELL, UART_SHELL_INSTANCE) == XST_FAILURE) {
		xil_printf("UART Shell Initialization Failed\r\n");
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
