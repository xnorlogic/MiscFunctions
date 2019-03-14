#include <stdio.h>
#include "MonotonicCheck.h"
#include "CheckSumCalc.h"

BarCode GenericBarCode = {
	0U, /*SID*/
	0U, /*HID*/
	0U, /*Format*/
	{0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U}, /*SN*/
	{0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,/*Data*/
	 0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,
	 0U,0U,0U,0U,0U,0U,0U,0U,0U},
	0U,/*Padding*/
	0U,/*Checksum*/
};

#define CHECKSUM_SIZE 6U

unsigned char data[CHECKSUM_SIZE]={0x10,0x11,0x12,0x13,0x14,0xa6};

void MonotonicTest(void);

int main(void){
	MonotonicTest();
	printf("\n0x%x",CheckSum_Calculator((unsigned char*)&data,CHECKSUM_SIZE));
  return 0;
}

void MonotonicTest(void){
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

}
