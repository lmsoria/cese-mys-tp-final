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
    memcpy((uint8_t*)m_key, key, 16);

    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG4_OFFSET, m_key[0]);
    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG5_OFFSET, m_key[1]);
    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG6_OFFSET, m_key[2]);
    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG7_OFFSET, m_key[3]);
}

void encoder_encode_data(uint8_t* src, uint8_t* dst)
{
	memcpy((uint8_t*)m_plain_text, src, 16);

    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG0_OFFSET, m_plain_text[0]);
    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG1_OFFSET, m_plain_text[1]);
    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG2_OFFSET, m_plain_text[2]);
    AES_128_ENCODER_mWriteReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG3_OFFSET, m_plain_text[3]);

	m_cipher_text[0] = AES_128_ENCODER_mReadReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG8_OFFSET);
	m_cipher_text[1] = AES_128_ENCODER_mReadReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG9_OFFSET);
	m_cipher_text[2] = AES_128_ENCODER_mReadReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG10_OFFSET);
	m_cipher_text[3] = AES_128_ENCODER_mReadReg(m_encoder_address, AES_128_ENCODER_S_AXI_SLV_REG11_OFFSET);

	memcpy(dst, (uint8_t*)m_cipher_text, 16);
}

const uint32_t* const encoder_get_key() { return m_key; }

const uint32_t* const encoder_get_plain_text() { return m_plain_text; }

const uint32_t* const encoder_get_cipher_text() { return m_cipher_text; }

// === End of documentation ======================================================================================== //
