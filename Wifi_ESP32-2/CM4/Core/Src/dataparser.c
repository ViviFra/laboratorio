#include "dataparser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "stdint.h"

unsigned int TX_Flag_DSTART = 0; /*Flag to turn on the drone*/
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
		case 'N': {
			TX_Flag_DSTART = 1;
		}
			break;

		case 'F': {
			TX_Flag_DSTART = 0;
		}
			break;

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

