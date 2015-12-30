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
	char first[] = {0xd4, 0x27, 0x11, 0xae, 0xe0, 0xbf, 0x98, 0xf1, 0xb8, 0xb4, 0x5d, 0xe5, 0x1e, 0x41, 0x52, 0x30};
	char second = 0x13;
	int word = 0xcf4f3c09;
	shiftRows(first);

	for(int i = 0; i < 16; i++){
		if(i % 4 == 0)
			printf("\n\r");
		printf("%x ", first[i]);
	}
}
