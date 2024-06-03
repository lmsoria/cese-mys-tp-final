/**********************************************************************************************************************
Copyright (c) 2024, Leandro Soria <leandromsoria@gmail.com>

Some fancy copyright message here (if needed)
**********************************************************************************************************************/

#pragma once

///
/// @file encoder.h
/// @brief AES-128 Encoder Driver (API)
///

// === Headers files inclusions ==================================================================================== //

#include <stdint.h>

// === C++ Guard =================================================================================================== //

#ifdef __cplusplus
extern "C" {
#endif

// === Public macros definitions =================================================================================== //
// === Public data type declarations =============================================================================== //
// === Public variable declarations ================================================================================ //
// === Public function declarations ================================================================================ //

void encoder_initialize(const uint32_t device_id);

void encoder_set_key(const uint8_t* key);

void encoder_encode_data(uint8_t* src, uint8_t* dst);

const uint32_t* const encoder_get_key();
const uint32_t* const encoder_get_plain_text();
const uint32_t* const encoder_get_cipher_text();

// === End of documentation ======================================================================================== //

#ifdef __cplusplus
}
#endif
