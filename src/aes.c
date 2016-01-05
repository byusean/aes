/*
 * aes.c
 *
 *  Created on: Dec 29, 2015
 *      Author: sean
 */
#include "aes.h"
#include <stdio.h>
#include "constants.h"

void cipher(char in[4*Nb], char out[4*Nb], int w[Nb*(Nr+1)])
{
	char state[4*Nb];
	char* roundPointer = (char *)w;

	for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
	{
		state[i] = in[i];
	}

//	printf("\n\rStart\n");
//	for(int i = 0; i < 4; i++)
//	{
//		printf("%8x ", state[i]);
//		printf("%8x ", state[i+4]);
//		printf("%8x ", state[i+8]);
//		printf("%8x\n", state[i+12]);
//	}

//	printf("\nRound Key Value\n");
//	for(int i = 0; i < 4; i++)
//	{
//		printf("%8x ", roundPointer[i]);
//		printf("%8x ", roundPointer[i+4]);
//		printf("%8x ", roundPointer[i+8]);
//		printf("%8x\n", roundPointer[i+12]);
//	}
//	printf("\nk_sch\n");
//	for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
//	{
//		printf("%9x", roundPointer[i]);
//	}

	addRoundKey(state, (char *)w);

	for(int round = 1; round <= Nr-1; round++)
	{
//		printf("\nStart of Round %d\n", round);
//		for(int i = 0; i < 4; i++)
//		{
//			printf("%8x ", state[i]);
//			printf("%8x ", state[i+4]);
//			printf("%8x ", state[i+8]);
//			printf("%8x\n", state[i+12]);
//		}
//		printf("\n-------------------------------------------------------------------------------------------------------------------------------\n");
//		printf("start\n");
//		for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
//		{
//			printf("%9x", state[i]);
//		}
		subBytes(state);
//		printf("\ns_box\n");
//		for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
//		{
//			printf("%9x", state[i]);
//		}
		shiftRows(state);
//		printf("\ns_row\n");
//		for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
//		{
//			printf("%9x", state[i]);
//		}
		mixColumns(state);
//		printf("\nm_col\n");
//		for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
//		{
//			printf("%9x", state[i]);
//		}
		roundPointer = (char *)(w+Nb*round);
//		printf("\nk_sch\n");
//		for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
//		{
//			printf("%9x", roundPointer[i]);
//		}
		addRoundKey(state, roundPointer);
	}

	subBytes(state);
	shiftRows(state);
	addRoundKey(state, (char *)(w+Nb*Nr));

	for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
	{
		out[i] = state[i];
	}
}

void invcipher(char in[4*Nb], char out[4*Nb], int w[Nb*(Nr+1)])
{
	char state[4*Nb];
	char* roundPointer = (char *)(w+Nb*Nr);

	for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
	{
		state[i] = in[i];
	}

//	printf("\nik_sch\n");
//	for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
//	{
//		printf("%9x", roundPointer[i]);
//	}
	addRoundKey(state, (char *)(w+Nb*Nr));

	for(int round = Nr-1; round >= 1; round--)
	{
//		printf("\n-------------------------------------------------------------------------------------------------------------------------------\n");
//		printf("istart round %d\n", Nr - round);
//		for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
//		{
//			printf("%9x", state[i]);
//		}
		invShiftRows(state);
//		printf("\nis_row\n");
//		for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
//		{
//			printf("%9x", state[i]);
//		}
		invSubBytes(state);
//		printf("\nis_box\n");
//		for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
//		{
//			printf("%9x", state[i]);
//		}
		roundPointer = (char *)(w+Nb*round);
//		printf("\nik_sch\n");
//		for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
//		{
//			printf("%9x", roundPointer[i]);
//		}
		addRoundKey(state, roundPointer);
		invMixColumns(state);
	}

	invShiftRows(state);
	invSubBytes(state);
	addRoundKey(state, (char *)w);

	for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
	{
		out[i] = state[i];
	}
}

void keyExpansion(char key[4*Nk], int w[Nb*(Nr+1)], char keyWordLength)
{
	int temp;
	char* ptr = (char *)w;
	for(int i = 0; i < keyWordLength*4; i++)
	{
		ptr[i] = key[i];
	}

	for(int i = keyWordLength; i < Nb*(Nr+1); i++)
	{
		temp = w[i-1];
//		printf("temp = 0x%x\n", temp);
		if(i % Nk == 0)
		{
			rotWord(&temp);
//			printf("after rotWord = 0x%x\n", temp);
			subWord(&temp);
//			printf("after subword = 0x%x\n", temp);
//			printf("Rcon[i/Nk] = 0x%x\n", Rcon[i/Nk]);
			temp ^= (Rcon[i/Nk] >> 24) & 0xFF;
//			printf("after xor with Rcon = 0x%x\n", temp);
		}
		else if(keyWordLength > 6 && i % keyWordLength == 4)
		{
			subWord(&temp);
		}
//		printf("w[i-Nk] = 0x%x\n", w[i-Nk]);
		w[i] = w[i-Nk] ^ temp;
//		printf("w[i] = 0x%x\n\r", w[i]);
	}
}

/**
 * second is modified
 */
void ffAdd(char* first, char* second)
{
	for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
	{
		second[i] = first[i] ^ second[i];
	}
}

char xtime(char byte)
{
	char topBitSet = byte & TOP_BIT_CHAR;
	if(topBitSet)
		return (byte << 1) ^ 0x1b;
	else
		return (byte << 1);
}

char numTime(char byte, char num)
{
	char accumulator = 0;
	char myByte = byte;

	//For an odd number
	if(num & 1)
		accumulator = myByte;
	else
		accumulator = 0;

	for(int j = 1; j < BYTE_SIZE; j++)
	{
		myByte = xtime(myByte);
		if(num & (1 << j))
			accumulator ^= myByte;
	}

	return accumulator;
}

/**
 * second is modified
 */
void chartime(char* first, char* second)
{
	char accumulator = 0;
	char myByte = *first;

	//For an odd number
	if(*second & 1)
		accumulator = myByte;
	else
		accumulator = 0;

	for(int j = 1; j < BYTE_SIZE; j++)
	{
		myByte = xtime(myByte);
		if(*second & (1 << j))
			accumulator ^= myByte;
	}

	*second = accumulator;
}

/**
 * second is modified
 */
void ffMultiply(char* first, char* second)
{
	for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
	{
		chartime(first + i, second + i);
	}
}

void subWord(int* word)
{
	char* ptr = (char *)word;
	for(int i = 0; i < BYTES_IN_A_WORD; i++)
	{
		int row = (*ptr >> NIBBLE_SIZE) & LOWER_NIBBLE;
		int col = (*ptr) & LOWER_NIBBLE;
		*ptr = Sbox[row][col];
		ptr++;
	}
}

void rotWord(int* word)
{
	char* ptr = (char *)word;
	char temp = ptr[3];
	ptr[3] = ptr[0];
	ptr[0] = ptr[1];
	ptr[1] = ptr[2];
	ptr[2] = temp;
}

/**
 * field is modified
 */
void subBytes(char* field)
{
	for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
	{
		int row = (field[i] >> NIBBLE_SIZE) & LOWER_NIBBLE;
		int col = (field[i]) & LOWER_NIBBLE;
		field[i] = Sbox[row][col];
	}
}

void shiftRows(char* field)
{
	//second row
	char temp = field[1];
	field[1] = field[5];
	field[5] = field[9];
	field[9] = field[13];
	field[13] = temp;

	//third row
	temp = field[2];
	field[2] = field[10];
	field[10] = temp;
	temp = field[6];
	field[6] = field[14];
	field[14] = temp;

	//fourth row
	temp = field[3];
	field[3] = field[15];
	field[15] = field[11];
	field[11] = field[7];
	field[7] = temp;
}

void mixColumns(char* field)
{
	int* word = (int *)field;
	for(int i = 0; i < WORDS_IN_STATE; i++)
	{
		char* baseChar = (char *)(word+i);
		char zero, one, two, three;

		zero = numTime(2,baseChar[0]) ^ numTime(3,baseChar[1]) ^ (baseChar[2]) ^ (baseChar[3]);
		one = (baseChar[0]) ^ numTime(2,baseChar[1]) ^ numTime(3,baseChar[2]) ^ (baseChar[3]);
		two = (baseChar[0]) ^ (baseChar[1]) ^ numTime(2,baseChar[2]) ^ numTime(3,baseChar[3]);
		three = numTime(3,baseChar[0]) ^ (baseChar[1]) ^ (baseChar[2]) ^ numTime(2,baseChar[3]);

		baseChar[0] = zero;
		baseChar[1] = one;
		baseChar[2] = two;
		baseChar[3] = three;
	}
}

void addRoundKey(char* word, char* roundKey)
{
	for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
	{
		word[i] = word[i] ^ roundKey[i];
	}
}

void invSubBytes(char* field)
{
	for(int i = 0; i < BYTES_IN_FOUR_WORDS; i++)
	{
		int row = (field[i] >> NIBBLE_SIZE) & LOWER_NIBBLE;
		int col = (field[i]) & LOWER_NIBBLE;
		field[i] = InvSbox[row][col];
	}
}

void invShiftRows(char* field)
{
	//second row
	char temp = field[1];
	field[1] = field[13];
	field[13] = field[9];
	field[9] = field[5];
	field[5] = temp;

	//third row
	temp = field[2];
	field[2] = field[10];
	field[10] = temp;
	temp = field[6];
	field[6] = field[14];
	field[14] = temp;

	//fourth row
	temp = field[3];
	field[3] = field[7];
	field[7] = field[11];
	field[11] = field[15];
	field[15] = temp;
}

void invMixColumns(char* field)
{
	int* word = (int *)field;
	for(int i = 0; i < WORDS_IN_STATE; i++)
	{
		char* baseChar = (char *)(word+i);
		char zero, one, two, three;

		zero = numTime(0xe,baseChar[0]) ^ numTime(0xb,baseChar[1]) ^ numTime(0xd,baseChar[2]) ^ numTime(0x9,baseChar[3]);
		one = numTime(0x9,baseChar[0]) ^ numTime(0xe,baseChar[1]) ^ numTime(0xb,baseChar[2]) ^ numTime(0xd,baseChar[3]);
		two = numTime(0xd,baseChar[0]) ^ numTime(0x9,baseChar[1]) ^ numTime(0xe,baseChar[2]) ^ numTime(0xb,baseChar[3]);
		three = numTime(0xb,baseChar[0]) ^ numTime(0xd,baseChar[1]) ^ numTime(0x9,baseChar[2]) ^ numTime(0xe,baseChar[3]);

		baseChar[0] = zero;
		baseChar[1] = one;
		baseChar[2] = two;
		baseChar[3] = three;
	}
}
