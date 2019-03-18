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
	uint_16 All_Z = 0;
	uint_16 All_F = 0;

	/*prevent a crash from a NULL pointer*/
	if (data != 0) {
		for (Index = 0U ; Index < DataSize ; Index++){
			BYTE_ELEMENT = data[Index];
			/*check is values is one or zero and accumulate for later use*/
			All_Z = (data[Index] == 0x00) + All_Z;
			All_F = (data[Index] == 0xff) + All_F;
			/*calculate checksum*/
			CheckSUM_calc = CheckSUM_calc + ((255U - BYTE_ELEMENT) + 1U);
		}
	}
	else{
		/* force checksum 0 */
		CheckSUM_calc = 0x00;
	}

	/*if and only if all of the data in the array is 0x00... give an incorrect checksum*/
	if(All_Z == dataSize - 1){
		CheckSUM_calc = 0xff;
	}

	/*if and only if all of the data in the array is 0xff... give an incorrect checksum*/
	if(All_F == dataSize - 1){
		CheckSUM_calc = 0x00;
	}

	/* Return statement for the checksum calculator */
	return CheckSUM_calc;
}
