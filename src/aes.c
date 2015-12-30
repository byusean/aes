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

}
