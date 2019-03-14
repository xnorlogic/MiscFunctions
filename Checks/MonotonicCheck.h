/*
 * MonotonicCheck.h
 *
 *  Created on: Mar 14, 2019
 *      Author: androdrigue2
 */

#ifndef MONOTONICCHECK_H_
#define MONOTONICCHECK_H_

/*application specific Data size*/
#define DATA_SIZE 	5U
/*scale factor*/
#define DATA_SCALE_FACTOR 		0.1f
/*fixed for a pay-load data type of U16*/
#define PAYLOAD_SIZE 			106U / 2U
/*SN fixed*/
#define SERIAL_NUMBER_SIZE 		17U

typedef struct{
	unsigned char  S_ID;
	unsigned char  H_ID;
	unsigned char  Format;
	unsigned char  SN[SERIAL_NUMBER_SIZE];
	unsigned short int Data[PAYLOAD_SIZE];
	unsigned char  Padding;
	unsigned char  CheckSum;
}BarCode;

unsigned char Monotonically_Inc_Chk(BarCode *GenericBarCode,unsigned char DATA_OFFSET);

#endif /* MONOTONICCHECK_H_ */
