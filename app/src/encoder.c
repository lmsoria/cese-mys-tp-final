/**********************************************************************************************************************
Copyright (c) 2024, Leandro Soria <leandromsoria@gmail.com>

Some fancy copyright message here (if needed)
**********************************************************************************************************************/

///
/// @file encoder.c
/// @brief AES-128 Encoder Driver (implementation)
///

// === Headers files inclusions ==================================================================================== //

#include "aes_128_encoder.h"
#include <string.h>
#include "xil_io.h"

#include "encoder.h"

// === Macros definitions ========================================================================================== //
// === Private data type declarations ============================================================================== //
// === Private variable declarations =============================================================================== //
// === Private function declarations =============================================================================== //
// === Public variable definitions ================================================================================= //
// === Private variable definitions ================================================================================ //

static uint32_t m_encoder_address = 0;
static uint32_t m_key[4] = {0};
static uint32_t m_plain_text[4] = {0};
static uint32_t m_cipher_text[4] = {0};

// === Private function implementation ============================================================================= //
// === Public function implementation ============================================================================== //


void encoder_initialize(const uint32_t device_id)
{
	m_encoder_address = device_id;

    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG0_OFFSET, m_plain_text[0]);
    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG1_OFFSET, m_plain_text[1]);
    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG2_OFFSET, m_plain_text[2]);
    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG3_OFFSET, m_plain_text[3]);

    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG4_OFFSET, m_key[0]);
    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG5_OFFSET, m_key[1]);
    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG6_OFFSET, m_key[2]);
    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG7_OFFSET, m_key[3]);
}

void encoder_set_key(const uint8_t* key)
{
    // Copy the bytes of the key into m_key, reordering for big-endian
    m_key[0] = (key[0] << 24) | (key[1] << 16) | (key[2] << 8) | key[3];
    m_key[1] = (key[4] << 24) | (key[5] << 16) | (key[6] << 8) | key[7];
    m_key[2] = (key[8] << 24) | (key[9] << 16) | (key[10] << 8) | key[11];
    m_key[3] = (key[12] << 24) | (key[13] << 16) | (key[14] << 8) | key[15];

    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG4_OFFSET, m_key[0]);
    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG5_OFFSET, m_key[1]);
    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG6_OFFSET, m_key[2]);
    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG7_OFFSET, m_key[3]);
}

void encoder_encode_data(uint8_t* src, uint8_t* dst)
{
    // Copy the bytes of the source data into m_plain_text, reordering for big-endian
    m_plain_text[0] = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
    m_plain_text[1] = (src[4] << 24) | (src[5] << 16) | (src[6] << 8) | src[7];
    m_plain_text[2] = (src[8] << 24) | (src[9] << 16) | (src[10] << 8) | src[11];
    m_plain_text[3] = (src[12] << 24) | (src[13] << 16) | (src[14] << 8) | src[15];

    // Write the plain text to the appropriate registers
    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG0_OFFSET, m_plain_text[0]);
    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG1_OFFSET, m_plain_text[1]);
    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG2_OFFSET, m_plain_text[2]);
    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG3_OFFSET, m_plain_text[3]);

    // Read the cipher text from the appropriate registers
    m_cipher_text[0] = AES_128_ENCODER_mReadReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG8_OFFSET);
    m_cipher_text[1] = AES_128_ENCODER_mReadReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG9_OFFSET);
    m_cipher_text[2] = AES_128_ENCODER_mReadReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG10_OFFSET);
    m_cipher_text[3] = AES_128_ENCODER_mReadReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG11_OFFSET);

    // Copy the bytes of the cipher text into the destination, reordering for big-endian
    dst[0] = (m_cipher_text[0] >> 24) & 0xFF;
    dst[1] = (m_cipher_text[0] >> 16) & 0xFF;
    dst[2] = (m_cipher_text[0] >> 8) & 0xFF;
    dst[3] = m_cipher_text[0] & 0xFF;

    dst[4] = (m_cipher_text[1] >> 24) & 0xFF;
    dst[5] = (m_cipher_text[1] >> 16) & 0xFF;
    dst[6] = (m_cipher_text[1] >> 8) & 0xFF;
    dst[7] = m_cipher_text[1] & 0xFF;

    dst[8] = (m_cipher_text[2] >> 24) & 0xFF;
    dst[9] = (m_cipher_text[2] >> 16) & 0xFF;
    dst[10] = (m_cipher_text[2] >> 8) & 0xFF;
    dst[11] = m_cipher_text[2] & 0xFF;

    dst[12] = (m_cipher_text[3] >> 24) & 0xFF;
    dst[13] = (m_cipher_text[3] >> 16) & 0xFF;
    dst[14] = (m_cipher_text[3] >> 8) & 0xFF;
    dst[15] = m_cipher_text[3] & 0xFF;
}

const uint32_t* const encoder_get_key() { return m_key; }

const uint32_t* const encoder_get_plain_text() { return m_plain_text; }

const uint32_t* const encoder_get_cipher_text() { return m_cipher_text; }

// === End of documentation ======================================================================================== //
