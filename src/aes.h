/*
 * aes.h
 *
 *  Created on: Dec 29, 2015
 *      Author: sean
 */

#ifndef AES_H_
#define AES_H_

#define LOWER_NIBBLE 0xF
#define TOP_BIT_CHAR 0x80
#define NIBBLE_SIZE 4
#define BYTES_IN_A_WORD 4
#define BYTE_SIZE 8
#define WORDS_IN_STATE 4
#define BYTES_IN_FOUR_WORDS 16

#define Nk 8
#define Nb 4
#define Nr 14

typedef enum{
	FAILURE,
	SUCCESS
} status;

void cipher(char in[4*Nb], char out[4*Nb], int w[Nb*(Nr+1)]);
void invcipher(char in[4*Nb], char out[4*Nb], int w[Nb*(Nr+1)]);
void keyExpansion(char key[4*Nk], int w[Nb*(Nr+1)], char keyWordLength);

void ffAdd(char* first, char* second);
void ffMultiply(char* first, char* second);

void subWord(int* word);
void rotWord(int* word);
void addRoundKey(char* word, char* roundKey);

void subBytes(char* field);
void shiftRows(char* field);
void mixColumns(char* field);

void invSubBytes(char* field);
void invShiftRows(char* field);
void invMixColumns(char* field);

#endif /* AES_H_ */
