#include "dataparser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "stdint.h"

unsigned int TX_Flag_DSEND = 0; /*Flag to start transmission*/

/**********************************************
 * Function name: clearBuffer
 * Description : Clear the buffer array
 * Argument : none
 * Return value : none
 **********************************************/
void clearCommand(uint8_t data[]) {
	int i;
	for (i = 0; i < sizeof(data); i++) {
		data[i] = 0;
	}
}

/**********************************************
 * Function name: parseCommand
 * Description : Parse the received command
 * Argument : none
 * Return value : Char* pointing to the parsed command
 **********************************************/
void parseCommand(char *data) {
	if (data[2]) {
		switch (data[2]) {

		case 'E': {
			TX_Flag_DSEND = 1;
		}
			break;

		case 'D': {
			TX_Flag_DSEND = 0;
		}
			break;

		default:
			break;
		}
	}
}

//crea rispetto ad un double di partenza un array
//di unsigned int con senza perdita di cifre significative
void getFixedArray(double num, int nInt, int nDec, uint8_t *result) {
	int p = 0;
	for (int i=0; ; i++) {
		int r = (int) num/pow(10,i);
		if (r == 0) {
			p = i;
			break;
		}
	}
	char temp[nInt+nDec+1];
	ftoa(num, temp, nDec);
	int j=0;
	for (int i=0; i<nInt; i++) {
		if (nInt-p-i <= 0) {
			result[i] = temp[j];
			j++;
		} else {
			result[i] = '0';
		}
	}
	if (p==0)
		j++;
	j++;
	for (int i=nInt; i<nInt+nDec; i++) {
		result[i] = temp[j];
		j++;
	}
}
