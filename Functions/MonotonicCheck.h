/*
 * MonotonicCheck.h
 *
 *  Created on: Mar 14, 2019
 *      Author: androdrigue2
 */

#ifndef MONOTONICCHECK_H_
#define MONOTONICCHECK_H_

#include "BarCode.h"

uint_8 Monotonically_Inc_Chk(BarCode *GenericBarCode,uint_8 DATA_OFFSET);
uint_8 Monotonically_Inc_Chk_GEN(uint_8* data,uint_8 dataSize);

#endif /* MONOTONICCHECK_H_ */
