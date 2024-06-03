/**********************************************************************************************************************
Copyright (c) 2024, Leandro Soria <leandromsoria@gmail.com>

Some fancy copyright message here (if needed)
**********************************************************************************************************************/

#pragma once

///
/// @file main.h
/// @brief Main Application Definitions and Globals
///

// === Headers files inclusions ==================================================================================== //
#include "xparameters.h"


// === C++ Guard =================================================================================================== //

#ifdef __cplusplus
extern "C" {
#endif

// === Public macros definitions =================================================================================== //

#define AES_INSTANCE (XPAR_AES_128_ENCODER_S_AXI_BASEADDR)
#define UART_SHELL_INSTANCE (XPAR_XUARTPS_0_DEVICE_ID)
#define UART_CRYPTO_INSTANCE (XPAR_XUARTPS_1_DEVICE_ID)
#define BAUDRATE (115200U)



// === Public data type declarations =============================================================================== //
// === Public variable declarations ================================================================================ //
// === Public function declarations ================================================================================ //
// === End of documentation ======================================================================================== //

#ifdef __cplusplus
}
#endif
