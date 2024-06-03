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
// === Private variable declarations =============================================================================== //
// === Private function declarations =============================================================================== //

static void print_bar(void);

// === Public variable definitions ================================================================================= //
// === Private variable definitions ================================================================================ //

static uint8_t key_buffer[16] = {0};

// === Private function implementation ============================================================================= //

static void print_bar(void) { xil_printf("----------------------------------------\n\r"); }

// === Public function implementation ============================================================================== //

int main(void)
{
	char running = 1;
	char echoing = 1;
	int index = 0;
	u8 RecvChar;

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
	xil_printf("Enter the AES-128 Key: ");

	while(running) {
		RecvChar = uart_read_byte(UART_SHELL);
		if (CHAR_ENTER == RecvChar) {
			running = 0;
		} else {
			key_buffer[index++] = RecvChar;

			if(index == 16) {
				running = FALSE;
			}
		}

		// Echo the character back
		uart_write_byte(UART_SHELL, RecvChar);
	}

	uart_write_bytes(UART_SHELL, (uint8_t*)"\r\n", 2);

	xil_printf("Setting key: %s ( ", key_buffer);
	for(uint8_t i = 0; i < 17; i++) {
		xil_printf("%02x ", key_buffer[i]);
	}
	xil_printf(")\r\n");

	xil_printf("Started echo service on UART1. \r\n");
	xil_printf("Messages typed here will be sent encrypted using the specified key.\r\n");
	print_bar();

	while(echoing) {
		RecvChar = uart_read_byte(UART_SHELL);
		if (CHAR_ESCAPE == RecvChar) {
			echoing = 0;
		}
		// Echo the character back
		uart_write_byte(UART_SHELL, RecvChar);
		uart_write_byte(UART_CRYPTO, RecvChar);
	}

	print_bar();
	xil_printf("AES-128 Encoder application stopped\n\r");
	print_bar();

	return XST_SUCCESS;
}

// === End of documentation ======================================================================================== //
