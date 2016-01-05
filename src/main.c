/*
 * main.c
 *
 *  Created on: Dec 30, 2015
 *      Author: sean
 */

#include <stdio.h>
#include "aes.h"

int main()
{
	char in[] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
	char inC[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
	int inC1_w[] = {0x33221100, 0x77665544, 0xbbaa9988, 0xffeeddcc};
	char* inC1_wptr = (char *)inC1_w;
	char out[16];
	char second = 0x57;
	int word = 0x8a84eb01;
	int cipherKeyA1[] = {0x16157e2b, 0xa6d2ae28, 0x8815f7ab, 0x3c4fcf09};
	int cipherKeyA2[] = {0x8e73b0f7, 0xda0e6452, 0xc810f32b, 0x809079e5, 0x62f8ead2, 0x522c6b7b};
	int cipherKeyA3[] = {0x603deb10, 0x15ca71be, 0x2b73aef0, 0x857d7781, 0x1f352c07, 0x3b6108d7, 0x2d9810a3, 0x0914dff4};
	int cipherKeyC1[] = {0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c};
	int cipherKeyC2[] = {0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c, 0x13121110, 0x17161514};
	int cipherKeyC3[] = {0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c, 0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c};
	char *cipherKeyC1_charptr = (char *)cipherKeyC1;
	int w[Nb*(Nr+1)];

//	for(int i = 0; i < 16; i++)
//	{
//		printf("%8x vs %8x\n", inC1[i], inC1_wptr[i]);
//	}

	//FOR DOING APPENDIX C1
	printf("\nInput\n");
	for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
	{
		printf("%9x", inC[i]);
	}
//	printf("\nCipher Key\n");
//	for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
//	{
//		printf("%9x", cipherKeyC1_charptr[i]);
//	}
	keyExpansion((char *)cipherKeyC3, w, Nk);
	printf("\n\rAfter the Key Expansion");
	for(int i = 0; i < Nb*(Nr+1); i++)
	{
		if(i % 4 == 0)
			printf("\n");
		printf("%9x ", w[i]);
	}
	for(int i = 0; i < Nb*(Nr+1); i++)
	{
		if(i % 8 == 0)
			printf("\n");
		printf("%9x ", w[i]);
	}
	cipher(inC, out, w);
	printf("\n\rAfter the Cipher\n");
	for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
	{
		printf("%9x", out[i]);
	}
	printf("\n");

	invcipher(out, inC, w);
	printf("\n\rAfter the InvCipher\n");
	for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
	{
		printf("%9x", inC[i]);
	}
	printf("\n");

	//FOR DOING APPENDIX A AND B
//	keyExpansion((char *)cipherKeyA1, w, Nk);
//	printf("\n\rAfter the operation");
//	for(int i = 0; i < Nb*(Nr+1); i++)
//	{
//		if(i % 4 == 0)
//			printf("\n\r");
//		printf("%9x ", w[i]);
//	}
//
//	cipher(in, out, w);
//	printf("\n\rAfter the Cipher\n");
//	for(int i = 0; i < 4; i++)
//	{
//		printf("%8x ", out[i]);
//		printf("%8x ", out[i+4]);
//		printf("%8x ", out[i+8]);
//		printf("%8x\n", out[i+12]);
//	}
}
