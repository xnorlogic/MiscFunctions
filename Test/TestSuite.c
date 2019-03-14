#include "MonotonicCheck.h"
#include "CheckSumCalc.h"

#define CHECKSUM_SIZE  6U
#define CHECKSUM_DATA_INDEX  CHECKSUM_SIZE - 1U

#define MONOTONIC_CHK_PASS_ID  3U
#define CHECKSUM_CHK_PASS_ID  4U

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

unsigned char MonotonicTest(void);
unsigned char ChecksumTest(void);

int main(void){
	unsigned char MasterCheck = 0U;

	MasterCheck = MonotonicTest() && ChecksumTest();

	return !MasterCheck;
}

unsigned char MonotonicTest(void){
	unsigned char MonotonicData = 0;

	/*Test 1 monotonic*/
	GenericBarCode.Data[0]=0;
	GenericBarCode.Data[1]=1;
	GenericBarCode.Data[2]=2;
	GenericBarCode.Data[3]=3;
	GenericBarCode.Data[4]=4;

	MonotonicData = Monotonically_Inc_Chk(&GenericBarCode,0);

	/*Test 2 no monotonic*/
	GenericBarCode.Data[0]=0;
	GenericBarCode.Data[1]=1;
	GenericBarCode.Data[2]=2;
	GenericBarCode.Data[3]=4;
	GenericBarCode.Data[4]=3;

	MonotonicData = Monotonically_Inc_Chk(&GenericBarCode,0) + MonotonicData;

	/*Test 3 monotonic*/
	GenericBarCode.Data[0]=0;
	GenericBarCode.Data[1]=1;
	GenericBarCode.Data[2]=2;
	GenericBarCode.Data[3]=4;
	GenericBarCode.Data[4]=4;

	MonotonicData = Monotonically_Inc_Chk(&GenericBarCode,0) + MonotonicData;

	/*Test 4 no monotonic*/
	GenericBarCode.Data[0]=0;
	GenericBarCode.Data[1]=1;
	GenericBarCode.Data[2]=5;
	GenericBarCode.Data[3]=5;
	GenericBarCode.Data[4]=4;

	MonotonicData = Monotonically_Inc_Chk(&GenericBarCode,0) + MonotonicData;

	/*Test 5 monotonic*/
	GenericBarCode.Data[0]=1;
	GenericBarCode.Data[1]=1;
	GenericBarCode.Data[2]=1;
	GenericBarCode.Data[3]=1;
	GenericBarCode.Data[4]=1;

	MonotonicData = Monotonically_Inc_Chk(&GenericBarCode,0) + MonotonicData;

	/*Test suite pass if and only if the monotonic checks match the MONOTONIC_CHK_PASS_ID*/
	/*3 monotinic data set and 2 non monotonic data sets*/
	/*TBD... cross check agains the Test ID Spec*/
	return (MonotonicData == MONOTONIC_CHK_PASS_ID);
}

unsigned char ChecksumTest(void){
	unsigned char CheckSumCheck = 0;

	unsigned char data0[CHECKSUM_SIZE]={0x10,0x11,0x12,0x13,0x14,0xa6}; /*OK Checksum*/
	unsigned char data1[CHECKSUM_SIZE]={0x14,0x12,0x10,0x11,0x14,0xa5}; /*OK Checksum*/
	unsigned char data2[CHECKSUM_SIZE]={0x14,0x14,0x14,0x12,0x12,0xa0}; /*OK Checksum*/
	unsigned char data3[CHECKSUM_SIZE]={0x10,0x10,0x10,0x10,0x10,0xb0}; /*OK Checksum*/
	unsigned char data4[CHECKSUM_SIZE]={0xaa,0xab,0xbb,0x12,0x12,0xa6}; /*Checksum in the data array incorrect*/

	CheckSumCheck = CheckSum_Calculator((unsigned char*)&data0,sizeof(data0)) == data0[CHECKSUM_DATA_INDEX];
	CheckSumCheck = (CheckSum_Calculator((unsigned char*)&data1,sizeof(data0)) == data1[CHECKSUM_DATA_INDEX]) + CheckSumCheck;
	CheckSumCheck = (CheckSum_Calculator((unsigned char*)&data2,sizeof(data0)) == data2[CHECKSUM_DATA_INDEX]) + CheckSumCheck;
	CheckSumCheck = (CheckSum_Calculator((unsigned char*)&data3,sizeof(data0)) == data3[CHECKSUM_DATA_INDEX]) + CheckSumCheck;
	CheckSumCheck = (CheckSum_Calculator((unsigned char*)&data4,sizeof(data0)) == data4[CHECKSUM_DATA_INDEX]) + CheckSumCheck;

	/*Test suite pass if and only if the checksum checks match the CHECKSUM_CHK_PASS_ID*/
	/*4 arrays with matching checksum, 1 array with no match on the checksum*/
	/*TBD... cross check agains the Test ID Spec*/
	return (CheckSumCheck == CHECKSUM_CHK_PASS_ID);
}
