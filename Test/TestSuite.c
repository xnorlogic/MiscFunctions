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

void MonotonicTest(void);
void ChecksumTest(void);

int main(void){
	MonotonicTest();
	ChecksumTest();
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

void ChecksumTest(void){
	unsigned char data0[CHECKSUM_SIZE]={0x10,0x11,0x12,0x13,0x14,0xa6};
	unsigned char data1[CHECKSUM_SIZE]={0x14,0x12,0x10,0x11,0x14,0xa5};
	unsigned char data2[CHECKSUM_SIZE]={0x14,0x14,0x14,0x12,0x12,0xa0};
	unsigned char data3[CHECKSUM_SIZE]={0x10,0x10,0x10,0x10,0x10,0xb0};
	unsigned char data4[CHECKSUM_SIZE]={0xaa,0xab,0xbb,0x12,0x12,0xa6};

	printf("\n%d",CheckSum_Calculator((unsigned char*)&data0,CHECKSUM_SIZE) == data0[5]);
	printf("%d",CheckSum_Calculator((unsigned char*)&data1,CHECKSUM_SIZE) == data1[5]);
	printf("%d",CheckSum_Calculator((unsigned char*)&data2,CHECKSUM_SIZE) == data2[5]);
	printf("%d",CheckSum_Calculator((unsigned char*)&data3,CHECKSUM_SIZE) == data3[5]);
	printf("%d",CheckSum_Calculator((unsigned char*)&data4,CHECKSUM_SIZE) == data4[5]);
}
