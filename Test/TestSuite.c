#include <stdio.h>
#include "MonotonicCheck.h"

BarCode GenericBarCode = {
	/* Supplier ID 		1   Byte  */
	0U,
	/* Hardware ID 		1   Byte  */
	0U,
	/* Format 			1   Byte  */
	0U,
	/* Serial Number 	17  Bytes */
	{0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U},
	/* Payload 			106 Bytes */
	{0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,
	 0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,
	 0U,0U,0U,0U,0U,0U,0U,0U,0U},
	/* Padding 			1   Byte  */
	0U,
	/* Check Sum 		1   Byte  */
	0U,
};

int main(void){
	unsigned char MonotonicDataFlag = 0;

	/*Test 1 monotonic*/
	GenericBarCode.Data[0]=0;
	GenericBarCode.Data[1]=1;
	GenericBarCode.Data[2]=2;
	GenericBarCode.Data[3]=3;
	GenericBarCode.Data[4]=4;

	MonotonicDataFlag = Monotonically_Inc_Chk(&GenericBarCode,0);

	printf("%d",MonotonicDataFlag);

	/*Test 2 no monotonic*/
	GenericBarCode.Data[0]=0;
	GenericBarCode.Data[1]=1;
	GenericBarCode.Data[2]=2;
	GenericBarCode.Data[3]=4;
	GenericBarCode.Data[4]=3;

	MonotonicDataFlag = Monotonically_Inc_Chk(&GenericBarCode,0);

	printf("%d",MonotonicDataFlag);

	/*Test 3 monotonic*/
	GenericBarCode.Data[0]=0;
	GenericBarCode.Data[1]=1;
	GenericBarCode.Data[2]=2;
	GenericBarCode.Data[3]=4;
	GenericBarCode.Data[4]=4;

	MonotonicDataFlag = Monotonically_Inc_Chk(&GenericBarCode,0);

	printf("%d",MonotonicDataFlag);

	/*Test 4 no monotonic*/
	GenericBarCode.Data[0]=0;
	GenericBarCode.Data[1]=1;
	GenericBarCode.Data[2]=5;
	GenericBarCode.Data[3]=5;
	GenericBarCode.Data[4]=4;

	MonotonicDataFlag = Monotonically_Inc_Chk(&GenericBarCode,0);

	printf("%d",MonotonicDataFlag);

	/*Test 5 monotonic*/
	GenericBarCode.Data[0]=1;
	GenericBarCode.Data[1]=1;
	GenericBarCode.Data[2]=1;
	GenericBarCode.Data[3]=1;
	GenericBarCode.Data[4]=1;

	MonotonicDataFlag = Monotonically_Inc_Chk(&GenericBarCode,0);

	printf("%d",MonotonicDataFlag);

  return 0;
}
