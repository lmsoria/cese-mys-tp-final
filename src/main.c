/*
 * main.c
 *
 *  Created on: 30 may. 2024
 *      Author: lsoria
 */
#include <stdint.h>
#include "aes_128_encoder.h"
#include "xil_io.h"
#include "xparameters.h"

#define AES_INSTANCE (XPAR_AES_128_ENCODER_0_S_AXI_BASEADDR)

int main(void)
{

	xil_printf("----------------------------------------\n\r");
	xil_printf("AES-128 Encoder application starts here\n\r");
	xil_printf("----------------------------------------\n\r");

	uint32_t plain_text[4] = {0x000000000, 0x000000000, 0x000000000, 0x000000000};
	uint32_t key[4] = {0x000000000, 0x000000000, 0x000000000, 0x000000000};
	uint32_t cipher_text[4] = {0x000000000, 0x000000000, 0x000000000, 0x000000000};

	AES_128_ENCODER_mWriteReg(AES_INSTANCE, AES_128_ENCODER_S_AXI_SLV_REG0_OFFSET, plain_text[0]);
	AES_128_ENCODER_mWriteReg(AES_INSTANCE, AES_128_ENCODER_S_AXI_SLV_REG1_OFFSET, plain_text[1]);
	AES_128_ENCODER_mWriteReg(AES_INSTANCE, AES_128_ENCODER_S_AXI_SLV_REG2_OFFSET, plain_text[2]);
	AES_128_ENCODER_mWriteReg(AES_INSTANCE, AES_128_ENCODER_S_AXI_SLV_REG3_OFFSET, plain_text[3]);

	AES_128_ENCODER_mWriteReg(AES_INSTANCE, AES_128_ENCODER_S_AXI_SLV_REG4_OFFSET, key[0]);
	AES_128_ENCODER_mWriteReg(AES_INSTANCE, AES_128_ENCODER_S_AXI_SLV_REG5_OFFSET, key[1]);
	AES_128_ENCODER_mWriteReg(AES_INSTANCE, AES_128_ENCODER_S_AXI_SLV_REG6_OFFSET, key[2]);
	AES_128_ENCODER_mWriteReg(AES_INSTANCE, AES_128_ENCODER_S_AXI_SLV_REG7_OFFSET, key[3]);

	cipher_text[0] = AES_128_ENCODER_mReadReg(AES_INSTANCE, AES_128_ENCODER_S_AXI_SLV_REG8_OFFSET);
	cipher_text[1] = AES_128_ENCODER_mReadReg(AES_INSTANCE, AES_128_ENCODER_S_AXI_SLV_REG9_OFFSET);
	cipher_text[2] = AES_128_ENCODER_mReadReg(AES_INSTANCE, AES_128_ENCODER_S_AXI_SLV_REG10_OFFSET);
	cipher_text[3] = AES_128_ENCODER_mReadReg(AES_INSTANCE, AES_128_ENCODER_S_AXI_SLV_REG11_OFFSET);

	xil_printf("Plain Text : %08x %08x %08x %08x\n\r", plain_text[0], plain_text[1], plain_text[2], plain_text[3]);
	xil_printf("Key        : %08x %08x %08x %08x\n\r", key[0], key[1], key[2], key[3]);
	xil_printf("Cipher Text: %08x %08x %08x %08x\n\r", cipher_text[0], cipher_text[1], cipher_text[2], cipher_text[3]);

	return 0;
}
