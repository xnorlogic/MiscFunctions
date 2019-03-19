#include "MonotonicCheck.h"

uint_8 Monotonically_Inc_Chk(BarCode *GenericBarCode,uint_8 DATA_OFFSET){
	uint_8 Index = 0U;
	uint_8 MonotonicallyIncCnt = 0U;
	uint_8 DataCheckSize = DATA_SIZE - 1U;
	float buffer_1 = 0.0f;
	float buffer_2 = 0.0f;

	for (Index = 0U; Index < DataCheckSize; Index++) {
		/* Extract and scale data element from the barcode data*/
		buffer_1 = GenericBarCode->Data[Index + DATA_OFFSET];
		buffer_1 *= DATA_SCALE_FACTOR;
		/* Extract and scale next data element from the barcode data*/
		buffer_2 = GenericBarCode->Data[(Index + DATA_OFFSET) + 1U];
		buffer_2 *= DATA_SCALE_FACTOR;
		/* Compare for monotonic increase data pair */
		if (buffer_1 <= buffer_2) {
			MonotonicallyIncCnt = MonotonicallyIncCnt + 1U;
		} 
	}

	/* Data Monotonically increasing if and only if all data is increasing */
	return (MonotonicallyIncCnt == DataCheckSize);
}

uint_8 Monotonically_Inc_Chk_GEN(uint_8* data,uint_8 dataSize){
	uint_8 Index = 0U;
	uint_8 MonotonicallyIncCnt = 0U;
	uint_8 DataCheckSize = dataSize - 1U;
	float buffer_1 = 0.0f;
	float buffer_2 = 0.0f;

	for (Index = 0U; Index < DataCheckSize; Index++) {
		buffer_1 = data[Index];
		buffer_2 = data[Index + 1U];
		/* Compare for monotonic increase data pair */
		if (buffer_1 <= buffer_2) {
			MonotonicallyIncCnt = MonotonicallyIncCnt + 1U;
		}
	}

	/* Data Monotonically increasing if and only if all data is increasing */
	return (MonotonicallyIncCnt == DataCheckSize);
}
