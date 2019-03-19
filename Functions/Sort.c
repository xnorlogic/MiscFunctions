/*
 * Sort.c
 *
 *  Created on: Mar 19, 2019
 *      Author: androdrigue2
 */

#include "Sort.h"

void Bubble_Sort(uint_8* data,uint_8 dataSize){
	uint_8 index = 0U;
	uint_8 swap_flag = 0U;
	do{
		swap_flag = 0U;
		for(index = 0U; index < dataSize - 1U ; index++){
			if(data[index] > data[index + 1U]){
				SWAP(data,index);
				swap_flag = 1U;
			}
		}
	}while(swap_flag == 1U);
}

void SWAP(uint_8* data,uint_8 index){
	uint_8 temp;
	temp = data[index + 1U];
	data[index + 1U] = data[index];
	data[index] = temp;
}
