/*
 * BarCode.h
 *
 *  Created on: Mar 14, 2019
 *      Author: androdrigue2
 */

#ifndef BARCODE_H_
#define BARCODE_H_

/*application specific Data size*/
#define DATA_SIZE             5U
/*scale factor*/
#define DATA_SCALE_FACTOR     0.1f
/*fixed for a pay-load data type of U16*/
#define PAYLOAD_SIZE          53U
/*SN fixed*/
#define SERIAL_NUMBER_SIZE    17U
/*Bar code size is 128 bytes*/
typedef struct{
	unsigned char  S_ID;
	unsigned char  H_ID;
	unsigned char  Format;
	unsigned char  SN[SERIAL_NUMBER_SIZE];
	unsigned short int Data[PAYLOAD_SIZE];
	unsigned char  Padding;
	unsigned char  CheckSum;
}BarCode;

#endif /* BARCODE_H_ */
