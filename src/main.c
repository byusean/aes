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
	char first = 0x53;
	char second = 0x13;
	int word = 0xcf4f3c09;
	subWord(&word);

	printf("result = %x\n\r", word);
}
