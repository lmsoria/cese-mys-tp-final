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

/// @brief Initialize the encoder by passing the device address.
/// Also initializes the key to be all zeroes.
/// @param device_id address of the encoder, taken from xparameters.h
void encoder_initialize(const uint32_t device_id);

/// @brief Set the encription key.
/// @param key must be 16 bytes long
void encoder_set_key(const uint8_t* key);

/// @brief Encode a chunk of 16 bytes using the previously given key. Therefore, `encoder_set_key()` must be called
/// before encoding any data, or otherwise it will use 16 zeroes as key.
/// @param src Data to encode. Must be 16 bytes long.
/// @param dst Where to store the data. Must be 16 bytes long.
void encoder_encode_data(uint8_t* src, uint8_t* dst);

/// @brief Key getter. Used for debugging purposes.
/// @return stored key
const uint32_t* const encoder_get_key();

/// @brief Plain text getter. Used for debugginig purposes.
/// @return stored plain text.
const uint32_t* const encoder_get_plain_text();

/// @brief Cipher text getter. Used for debugging purposes.
/// @return stored cipher text.
const uint32_t* const encoder_get_cipher_text();

// === End of documentation ======================================================================================== //

#ifdef __cplusplus
}
#endif
