#include "MonotonicCheck.h"
#include "CheckSumCalc.h"

#define CHECKSUM_SIZE  6U
#define CHECKSUM_DATA_INDEX  CHECKSUM_SIZE - 1U

#define MONOTONIC_CHK_PASS_ID  3U
#define CHECKSUM_CHK_PASS_ID 6U

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

uint_8 MonotonicTest(void);
uint_8 ChecksumTest(void);

int main(void){
	uint_8 MasterCheck = 0U;

	MasterCheck = MonotonicTest() && ChecksumTest();

	return !MasterCheck;
}

uint_8 MonotonicTest(void){
	uint_8 MonotonicData = 0;

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

uint_8 ChecksumTest(void){
	uint_8 CheckSumCheck = 0;

	uint_8 data0[CHECKSUM_SIZE]={0x10,0x11,0x12,0x13,0x14,0xa6}; /*OK Checksum*/
	uint_8 data1[CHECKSUM_SIZE]={0x14,0x12,0x10,0x11,0x14,0xa5}; /*OK Checksum*/
	uint_8 data2[CHECKSUM_SIZE]={0x14,0x14,0x14,0x12,0x12,0xa0}; /*OK Checksum*/
	uint_8 data3[CHECKSUM_SIZE]={0x10,0x10,0x10,0x10,0x10,0xb0}; /*OK Checksum*/
	uint_8 data4[CHECKSUM_SIZE]={0xaa,0xab,0xbb,0x12,0x12,0xa6}; /*Checksum in the data array incorrect*/

	uint_8 data5[CHECKSUM_SIZE]={0x00,0x00,0x00,0x00,0x00,0x00}; /*all 0x00 data array*/
	uint_8 data6[CHECKSUM_SIZE]={0xff,0xff,0xff,0xff,0xff,0x05}; /*all 0xff data array*/

	CheckSumCheck = CheckSum_Calculator((uint_8*)&data0,sizeof(data0)) == data0[CHECKSUM_DATA_INDEX];
	CheckSumCheck = (CheckSum_Calculator((uint_8*)&data1,sizeof(data0)) == data1[CHECKSUM_DATA_INDEX]) + CheckSumCheck;
	CheckSumCheck = (CheckSum_Calculator((uint_8*)&data2,sizeof(data0)) == data2[CHECKSUM_DATA_INDEX]) + CheckSumCheck;
	CheckSumCheck = (CheckSum_Calculator((uint_8*)&data3,sizeof(data0)) == data3[CHECKSUM_DATA_INDEX]) + CheckSumCheck;
	CheckSumCheck = (CheckSum_Calculator((uint_8*)&data4,sizeof(data0)) == data4[CHECKSUM_DATA_INDEX]) + CheckSumCheck;

	CheckSumCheck = (CheckSum_Calculator((uint_8*)&data5,sizeof(data0)) == data5[CHECKSUM_DATA_INDEX]) + CheckSumCheck;
	CheckSumCheck = (CheckSum_Calculator((uint_8*)&data6,sizeof(data0)) == data6[CHECKSUM_DATA_INDEX]) + CheckSumCheck;

	/*Test suite pass if and only if the checksum checks match the CHECKSUM_CHK_PASS_ID*/
	/*4 arrays with matching checksum, 1 array with no match on the checksum*/
	/*1 array with all 0x00*/
	/*1 array with all 0xff*/
	/*TBD... cross check against the Test ID Spec*/
	return (CheckSumCheck == CHECKSUM_CHK_PASS_ID);
}
