#include "MonotonicCheck.h"

unsigned char Monotonically_Inc_Chk(BarCode *GenericBarCode,unsigned char DATA_OFFSET){
	unsigned char Index = 0U;
	unsigned char MonotonicallyIncCnt = 0U;
	unsigned char DataCheckSize = DATA_SIZE - 1U;
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
