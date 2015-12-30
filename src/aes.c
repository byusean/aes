/*
 * aes.c
 *
 *  Created on: Dec 29, 2015
 *      Author: sean
 */
#include "aes.h"
#include "constants.h"

/**
 * second is modified
 */
void ffAdd(char* first, char* second)
{
	for(int i = 0; i < FOUR_WORDS; i++)
	{
		second[i] = first[i] ^ second[i];
	}
}

/**
 * second is modified
 */
void xtime(char* first, char* second)
{
	char accumulator = 0;
	for(int j = 0; j < BYTE_SIZE; j++)
	{
		char mask = *second & (1 << j);
		if(mask)
		{
			accumulator ^= (*first << (mask-1));
		}
	}

	*second = accumulator;
}

/**
 * second is modified
 */
void ffMultiply(char* first, char* second)
{
	for(int i = 0; i < FOUR_WORDS; i++)
	{
		xtime(first + i, second + i);
	}
}

/**
 * field is modified
 */
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
	ptr[3] = ptr[2];
	ptr[2] = ptr[1];
	ptr[1] = ptr[0];
	ptr[0] = temp;
}

/**
 * field is modified
 */
void subBytes(char* field)
{
	for(int i = 0; i < FOUR_WORDS; i++)
	{
		int row = (field[i] >> NIBBLE_SIZE) & LOWER_NIBBLE;
		int col = (field[i]) & LOWER_NIBBLE;
		field[i] = Sbox[row][col];
	}
}

void shiftRows(char* field)
{

}
