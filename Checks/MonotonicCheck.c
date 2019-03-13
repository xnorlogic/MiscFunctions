U8 Monotonically_Inc_Chk(BarCode *GenericBarCode,U8 DATA_OFFSET){
	U8 Index = 0U;
	U8 Monotonically_Inc_Cnt = 0U;
	U8 Monotonically_Inc_Chk_Flag = 0U;
	F32 buffer_1 = 0.0f;
	F32 buffer_2 = 0.0f;

	for (Index = 0U; Index < DATA_SIZE - 1U; Index++) {
		/* Extract and scale data element from the barcode data*/
		buffer_1 = GenericBarCode->Data[Index + DATA_OFFSET];
		buffer_1 /= DATA_SCALE_FACTOR;
		/* Extract and scale next data element from the barcode data*/
		buffer_2 = GenericBarCode->Data[(Index + DATA_OFFSET) + 1U];
		buffer_2 /= DATA_SCALE_FACTOR;
		/* Compare for monotonically increasing data */
		if (buffer_1 <= buffer_2) {
			Monotonically_Inc_Cnt = Monotonically_Inc_Cnt + 1U;
		} 
	}

	/* Torque Monotonically increasing if and only if all data is increasing */
	Monotonically_Inc_Chk_Flag = (Monotonically_Inc_Cnt == TORQUE_CURVE_DATA_SIZE - 1U);

	return Monotonically_Inc_Chk_Flag;
}
