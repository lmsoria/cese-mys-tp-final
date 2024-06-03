/**********************************************************************************************************************
Copyright (c) 2024, Leandro Soria <leandromsoria@gmail.com>

Some fancy copyright message here (if needed)
**********************************************************************************************************************/

#pragma once

///
/// @file uart.h
/// @brief Helper API to handle UART peripherals
///

// === Headers files inclusions ==================================================================================== //
#include <stdint.h>

// === C++ Guard =================================================================================================== //

#ifdef __cplusplus
extern "C" {
#endif

// === Public macros definitions =================================================================================== //

/// Baudrate used by the application. Will be the same for all UART peripherals.
#define BAUDRATE (115200U)

// === Public data type declarations =============================================================================== //

/// @brief Enum listing the available UART peripherals
typedef enum
{
    UART_SHELL = 0, ///< Used for User Interaction.
    UART_CRYPTO,    ///< Used for sending encrypted data.
    UART_TOTAL ///< Keep this value always at the bottom!
} UARTInstance;

// === Public variable declarations ================================================================================ //
// === Public function declarations ================================================================================ //

/// @brief Initialize the UART peripheral.
/// @param instance Peripheral to initialize.
/// @param device_id PL-PS Device ID. Should be obtained from xparameters.h
/// @return XST_SUCCESS on success, XST_FAILURE otherwise.
int uart_initialize(const UARTInstance instance, const uint16_t device_id);

/// @brief Read a byte from the specified UART. This function is blocking.
/// @param instance Peripheral to read.
/// @return Byte read.
uint8_t uart_read_byte(const UARTInstance instance);

/// @brief Write a single byte to the specified UART.
/// @param instance Peripheral to write.
/// @param data to be sent.
void uart_write_byte(const UARTInstance instance, uint8_t data);

/// @brief Write `length` bytes to the specified UART
/// @param instance Peripheral to write.
/// @param data to be sent.
/// @param length number of bytes to be sent.
void uart_write_bytes(const UARTInstance instance, uint8_t* data, size_t length);

// === End of documentation ======================================================================================== //

#ifdef __cplusplus
}
#endif
