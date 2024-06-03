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
#include "xuartps.h"
#include "sleep.h"

#include "main.h"

// === Macros definitions ========================================================================================== //

#define CHAR_ENTER		0x0D	/* 'ESC' character is used as terminator */
#define CHAR_ESCAPE		0x1B	/* 'ESC' character is used as terminator */


// === Private data type declarations ============================================================================== //
// === Private variable declarations =============================================================================== //
// === Private function declarations =============================================================================== //

static int initialize_uart_crypto(const uint16_t device_id);
static int initialize_uart_shell(const uint16_t device_id);

static uint8_t uart_read_byte(XUartPs* const uart_id);
static void uart_write_byte(XUartPs* const uart_id, uint8_t data);
static void uart_write_bytes(XUartPs* const uart_id, uint8_t* data, size_t length);

// === Public variable definitions ================================================================================= //
// === Private variable definitions ================================================================================ //

static XUartPs uart_crypto;
static XUartPs uart_shell;

uint8_t key_buffer[16] = {0};

const char* ENTER_KEY_MESSAGE = "Enter the AES-128 Key: ";


// === Private function implementation ============================================================================= //

static int initialize_uart_crypto(const uint16_t device_id)
{
	// Initialize the UART driver so that it's ready to use
	// Look up the configuration in the config table and then initialize it.
	XUartPs_Config* const UART_CONFIG = XUartPs_LookupConfig(device_id);
	if (UART_CONFIG == NULL) {
		return XST_FAILURE;
	}

	if (XUartPs_CfgInitialize(&uart_crypto, UART_CONFIG, UART_CONFIG->BaseAddress) != XST_SUCCESS) {
		return XST_FAILURE;
	}

	if( XUartPs_SetBaudRate(&uart_crypto, BAUDRATE) != XST_SUCCESS) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

static int initialize_uart_shell(const uint16_t device_id)
{
	// Initialize the UART driver so that it's ready to use
	// Look up the configuration in the config table and then initialize it.
	XUartPs_Config* const UART_CONFIG = XUartPs_LookupConfig(device_id);
	if (UART_CONFIG == NULL) {
		return XST_FAILURE;
	}

	if (XUartPs_CfgInitialize(&uart_shell, UART_CONFIG, UART_CONFIG->BaseAddress) != XST_SUCCESS) {
		return XST_FAILURE;
	}

	if( XUartPs_SetBaudRate(&uart_shell, BAUDRATE) != XST_SUCCESS) {
		return XST_FAILURE;
	}

//	u32 CntrlRegister;

//	CntrlRegister = XUartPs_ReadReg(XPAR_XUARTPS_0_BASEADDR, XUARTPS_CR_OFFSET);

//	/* Enable TX and RX for the device */
//	XUartPs_WriteReg(XPAR_XUARTPS_0_BASEADDR, XUARTPS_CR_OFFSET,
//			  ((CntrlRegister & ~XUARTPS_CR_EN_DIS_MASK) |
//			   XUARTPS_CR_TX_EN | XUARTPS_CR_RX_EN));

	return XST_SUCCESS;
}

static uint8_t uart_read_byte(XUartPs* const uart_id)
{
	uint8_t data;
	uint32_t bytes_read = XUartPs_Recv(uart_id,  &data, 1);

	return data;
}

static void uart_write_byte(XUartPs* const uart_id, uint8_t data)
{
//	XUartPs_WriteReg(device_id,  XUARTPS_FIFO_OFFSET, data);
	XUartPs_Send(uart_id, &data, 1);

}

static void uart_write_bytes(XUartPs* const uart_id, uint8_t* data, size_t length)
{
	XUartPs_Send(uart_id, data, length);

}

// === Public function implementation ============================================================================== //

int main(void)
{
	char running = 1;
	char echoing = 1;
	int index = 0;
	u8 RecvChar;

	if (initialize_uart_crypto(UART_CRYPTO_INSTANCE) == XST_FAILURE) {
		xil_printf("UART Crypto Initialization Failed\r\n");
		return XST_FAILURE;
	}
	if (initialize_uart_shell(UART_SHELL_INSTANCE) == XST_FAILURE) {
		xil_printf("UART Shell Initialization Failed\r\n");
		return XST_FAILURE;
	}

	xil_printf("----------------------------------------\n\r");
	xil_printf("AES-128 Encoder application starts here\n\r");
	xil_printf("----------------------------------------\n\r");
	xil_printf("%s", ENTER_KEY_MESSAGE);


	while(running) {
		 /* Wait until there is data */
		while (!XUartPs_IsReceiveData(XPAR_XUARTPS_0_BASEADDR));
		RecvChar = uart_read_byte(&uart_shell);
		if (CHAR_ENTER == RecvChar) {
			running = 0;
		} else {
			key_buffer[index++] = RecvChar;

			if(index == 16) {
				running = FALSE;
			}
		}

		// Echo the character back
		uart_write_byte(&uart_shell, RecvChar);
	}

	uart_write_bytes(&uart_shell, "\r\n", 2);

	xil_printf("\r\Setting key: %s ( ", key_buffer);
	for(uint8_t i = 0; i < 17; i++) {
		xil_printf("%02x ", key_buffer[i]);
	}
	xil_printf(")\r\n");

	xil_printf("Started echo service on UART1. \r\n");
	xil_printf("Messages typed here will be sent encrypted using the specified key.\r\n");
	xil_printf("----------------------------------------\n\r");


	while(echoing) {
		 /* Wait until there is data */
		while (!XUartPs_IsReceiveData(XPAR_XUARTPS_0_BASEADDR));
		RecvChar = uart_read_byte(&uart_shell);
		if (CHAR_ESCAPE == RecvChar) {
			echoing = 0;
		}
		// Echo the character back
		uart_write_byte(&uart_crypto, RecvChar);
		uart_write_byte(&uart_shell, RecvChar);
	}

	xil_printf("----------------------------------------\n\r");
	xil_printf("AES-128 Encoder application stopped\n\r");
	xil_printf("----------------------------------------\n\r");


	return XST_SUCCESS;
}

// === End of documentation ======================================================================================== //
