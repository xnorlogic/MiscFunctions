/*
 * CheckSumCalc.c
 *
 *  Created on: Mar 14, 2019
 *      Author: androdrigue2
 */

#include "CheckSumCalc.h"

uint_8 CheckSum_Calculator(uint_8* data){
	/* Check Sum accumulator */
	uint_8 CheckSUM_calc = 0U;
	uint_8 Index 	    = 0U;
	uint_8 BYTE_ELEMENT  = 0U;
	uint_8 DataSize = sizeof(data) - 1U;
	/*prevent a crash from a NULL pointer*/
	if (data != 0) {
		for (Index = 0U ; Index < DataSize ; Index++){
			BYTE_ELEMENT = data[Index];
			CheckSUM_calc = CheckSUM_calc + ((255U - BYTE_ELEMENT) + 1U);
		}
	}
	else{
		/* force checksum 0 */
		CheckSUM_calc = 0U;
	}
	/* Return statement for the checksum calculator */
	return CheckSUM_calc;
}

uint_8 CheckSum_chk(uint_8* data){
	uint_8 Check;

	Check = CheckSum_Calculator((uint_8*)&data) == data[sizeof(data) - 1U];

	/* Return statement for the checksum calculator */
	return Check;
}
