#include "MonotonicCheck.h"
#include "CheckSumCalc.h"
#include "Sort.h"

#define CHECKSUM_SIZE  6U
#define CHECKSUM_DATA_INDEX  CHECKSUM_SIZE - 1U

#define MONOTONIC_CHK_PASS_ID  3U
#define CHECKSUM_CHK_PASS_ID 4U
#define SORT_CHK_PASS_ID 6U

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
uint_8 SortTest_A(void);

int main(void){
	uint_8 MasterCheck = 0U;

	MasterCheck = MonotonicTest() && ChecksumTest() && SortTest_A();

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
	/*1 array with all 0x00 this should not generate an OK checksum*/
	/*1 array with all 0xff this should not generate an OK checksum*/
	/*TBD... cross check against the Test ID Spec*/
	return (CheckSumCheck == CHECKSUM_CHK_PASS_ID);
}

uint_8 SortTest_A(void){
	uint_8 SortCheck = 0;

	uint_8 data0[6]={5,7,4,9,9,1};
	uint_8 data1[6]={5,5,4,6,9,2};
	uint_8 data2[6]={4,7,4,9,9,1};
	uint_8 data3[6]={2,7,6,7,9,0};
	uint_8 data4[6]={5,6,6,6,6,1};

	uint_8 data5[255]={200,192,185,25,88,137,220,253,250,198,13,222,130,55,
			             1,75,124,135,17,221,93,36,176,95,191,172,170,254,
						 17,176,121,127,36,71,251,125,111,65,164,105,187,239,
						 206,5,18,166,102,151,246,122,104,205,6,160,25,228,48,
						 148,173,182,68,113,30,151,134,144,29,221,0,4,101,211,
						 75,249,162,21,143,14,134,204,42,179,5,237,158,128,45,
						 10,187,247,100,102,84,21,229,52,104,243,20,14,241,7,
						 176,46,123,42,96,175,177,164,252,208,198,159,155,48,210,
						 165,171,207,161,52,237,9,227,120,58,35,221,240,225,177,
						 245,18,56,226,22,218,27,3,15,154,187,10,157,35,178,92,24,
						 157,249,243,130,209,215,143,126,250,159,242,53,28,19,123,
						 158,159,102,5,15,50,21,66,60,135,108,91,145,51,50,27,142,
						 202,162,46,164,226,233,106,253,153,137,112,218,6,36,177,
						 131,146,29,103,195,32,116,215,13,103,179,81,113,232,138,
						 126,102,22,183,20,91,174,137,132,179,231,254,6,231,236,
						 194,28,195,43,83,212,120,95,36,48,234,107,150,80,101,122,
						 69,3,138,41,199,243,201,122,245,133,185,20,131};

	SortCheck = Monotonically_Inc_Chk_GEN((uint_8*)&data0,sizeof(data0)) + SortCheck;
	Bubble_Sort((uint_8*)&data0,sizeof(data0));
	SortCheck = Monotonically_Inc_Chk_GEN((uint_8*)&data0,sizeof(data0)) + SortCheck;

	SortCheck = Monotonically_Inc_Chk_GEN((uint_8*)&data1,sizeof(data1)) + SortCheck;
	Bubble_Sort((uint_8*)&data1,sizeof(data1));
	SortCheck = Monotonically_Inc_Chk_GEN((uint_8*)&data1,sizeof(data1)) + SortCheck;

	SortCheck = Monotonically_Inc_Chk_GEN((uint_8*)&data2,sizeof(data2)) + SortCheck;
	Bubble_Sort((uint_8*)&data2,sizeof(data2));
	SortCheck = Monotonically_Inc_Chk_GEN((uint_8*)&data2,sizeof(data2)) + SortCheck;

	SortCheck = Monotonically_Inc_Chk_GEN((uint_8*)&data3,sizeof(data3)) + SortCheck;
	Bubble_Sort((uint_8*)&data3,sizeof(data3));
	SortCheck = Monotonically_Inc_Chk_GEN((uint_8*)&data3,sizeof(data3)) + SortCheck;

	SortCheck = Monotonically_Inc_Chk_GEN((uint_8*)&data4,sizeof(data4)) + SortCheck;
	Bubble_Sort((uint_8*)&data4,sizeof(data4));
	SortCheck = Monotonically_Inc_Chk_GEN((uint_8*)&data4,sizeof(data4)) + SortCheck;

	SortCheck = Monotonically_Inc_Chk_GEN((uint_8*)&data5,sizeof(data5)) + SortCheck;
	Bubble_Sort((uint_8*)&data5,sizeof(data5));
	SortCheck = Monotonically_Inc_Chk_GEN((uint_8*)&data5,sizeof(data5)) + SortCheck;

	return (SortCheck == SORT_CHK_PASS_ID);
}
