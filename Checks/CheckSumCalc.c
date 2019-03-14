/*
 * CheckSumCalc.c
 *
 *  Created on: Mar 14, 2019
 *      Author: androdrigue2
 */

unsigned char CheckSum_Calculator(unsigned char* data,unsigned char dataSize){
	/* Check Sum accumulator */
	unsigned char CheckSUM_calc = 0U;
	unsigned char Index 	    = 0U;
	unsigned char BYTE_ELEMENT  = 0U;
	/*prevent a crash from a NULL pointer*/
	if (data != 0) {
		for (Index = 0U ; Index < dataSize - 1 ; Index++){
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
