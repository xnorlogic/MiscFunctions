#include <stdio.h>

/*application specific Data size*/
#define DATA_SIZE 	16U
/*scale factor*/
#define DATA_SCALE_FACTOR 		0.1f

typedef struct{
	U8  S_ID;
	U8  H_ID;
	U8  Format;
	U8  SN[SERIAL_NUMBER_SIZE];
	U16 Data[PAYLOAD_SIZE];
	U8  Padding;
	U8  CheckSum;
}BarCode;

BarCode GenericBarCode;

U8 BW_Monotonically_Inc_Chk(BarCode *,U8);

int main(void){

  return 0;
}
