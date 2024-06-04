/**********************************************************************************************************************
Copyright (c) 2024, Leandro Soria <leandromsoria@gmail.com>

Some fancy copyright message here (if needed)
**********************************************************************************************************************/

///
/// @file uart.c
/// @brief Helper API to handle UART peripherals (implementation)
///

// === Headers files inclusions ==================================================================================== //

#include "xstatus.h"
#include "xuartps.h"

#include "uart.h"

// === Macros definitions ========================================================================================== //
// === Private data type declarations ============================================================================== //
// === Private variable declarations =============================================================================== //

static XUartPs UART_PERIPHERALS[UART_TOTAL];
static uint32_t UART_ADDRESSES[UART_TOTAL];

// === Private function declarations =============================================================================== //
// === Public variable definitions ================================================================================= //
// === Private variable definitions ================================================================================ //
// === Private function implementation ============================================================================= //
// === Public function implementation ============================================================================== //

int uart_initialize(const UARTInstance instance, const uint16_t device_id)
{
    // Initialize the UART driver so that it's ready to use
    // Look up the configuration in the config table and then initialize it.
    XUartPs_Config* const UART_CONFIG = XUartPs_LookupConfig(device_id);
    if (UART_CONFIG == NULL) {
        return XST_FAILURE;
    }

    if (XUartPs_CfgInitialize(&UART_PERIPHERALS[instance], UART_CONFIG, UART_CONFIG->BaseAddress) != XST_SUCCESS) {
        return XST_FAILURE;
    }

    if( XUartPs_SetBaudRate(&UART_PERIPHERALS[instance], BAUDRATE) != XST_SUCCESS) {
        return XST_FAILURE;
    }

    UART_ADDRESSES[instance] = UART_CONFIG->BaseAddress;

    return XST_SUCCESS;
}

uint8_t uart_read_byte(const UARTInstance instance)
{
    uint8_t data = 0;
    while (!XUartPs_IsReceiveData(UART_ADDRESSES[instance]));
    (void)XUartPs_Recv(&UART_PERIPHERALS[instance],  &data, 1);
    return data;
}

void uart_write_byte(const UARTInstance instance, uint8_t data)
{
    XUartPs_Send(&UART_PERIPHERALS[instance], &data, 1);
}

void uart_write_bytes(const UARTInstance instance, uint8_t* data, size_t length)
{
    XUartPs_Send(&UART_PERIPHERALS[instance], data, length);
}

// === End of documentation ======================================================================================== //
