//
//  3727kadai2
//
//  Created by 田畑　凌 on 2017/05/17.
//  Copyright c 2017年 田畑　凌. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define N 100


int main(void){
	FILE *fp;
	fp=fopen("kadai-1-3.txt","r");
	if (fp ==NULL){
		printf("can't open file\n");
		exit(1);
	}
	int right, left, work, shift;
	int count=0;
	int i,j;
	int data[100]={0};
	
	for(i=0;i<100;i++){
		fscanf(fp,"%d",&data[i]);
	}
	fclose(fp);
	
	right = N-1; left = 0;
	while( right > left ){
		for( i=left; i<right; i++ ){
			if( data[i] > data[i+1] ){
				work = data[i];
				data[i] = data[i+1];
				data[i+1] = work;
				shift = i;
			}
		}
		right = shift;
		
		for( i=right; i>left; i-- ){
			if( data[i] < data[i-1] ){
				work = data[i];
				data[i] = data[i-1];
				data[i-1] = work;
				shift = i;
			}
		}
		left = shift;
	}
	
	for( i=0; i<N; i++ ){
		printf(" %2d", data[i]);
		count++;
		if(count%10==0)printf("\n");
	}
	
	return 0;
}
