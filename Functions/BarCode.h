/*
 * BarCode.h
 *
 *  Created on: Mar 14, 2019
 *      Author: androdrigue2
 */

#ifndef BARCODE_H_
#define BARCODE_H_

#include "types.h"

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
	uint_8  S_ID;
	uint_8  H_ID;
	uint_8  Format;
	uint_8  SN[SERIAL_NUMBER_SIZE];
	uint_16 Data[PAYLOAD_SIZE];
	uint_8  Padding;
	uint_8  CheckSum;
}BarCode;

#endif /* BARCODE_H_ */
