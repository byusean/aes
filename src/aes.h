/*
 * aes.h
 *
 *  Created on: Dec 29, 2015
 *      Author: sean
 */

#ifndef AES_H_
#define AES_H_

#define LOWER_NIBBLE 0xF
#define NIBBLE_SIZE 4
#define BYTES_IN_A_WORD 4
#define BYTE_SIZE 8
#define FOUR_WORDS 32

typedef enum{
	FAILURE,
	SUCCESS
} status;

void ffAdd(char* first, char* second);
void xtime(char* first, char* second);
void ffMultiply(char* first, char* second);
void subWord(int* word);
void rotWord(int* word);
void subBytes(char* field);
void shiftRows(char* field);

#endif /* AES_H_ */
