#include<stdio.h>
#include<stdlib.h>
#define N 10000000

void quicksort (int d[], int a, int b){
	int size=sizeof(d) / sizeof(int);
	if(size==1)return;
	int temp;
	int pivot;
	int last=b;
	int start=a;
	pivot = d[a];
	
	while (1){
		while (d[a]<pivot)a++;
		while(d[b]>pivot)b--;
		if(a>b)break;
		temp=d[a];
		d[a]=d[b];
		d[b]=temp;
	}
	if(a+1==b){
		temp=d[a];
		d[a]=pivot;
		pivot=d[a];
	}
	quicksort(d,start,a-1);
	quicksort(d,a+1,last);
	
}

int main()
{
	FILE *fp;
	int *num,h=0,size=0,next,lines=0,i=0;
	char str[10];
	
	fp= fopen ("kadai5-1.txt","r");
	if(fp==NULL){
		printf("file can't open\n");
		exit(1);
	}

	while ( fgets(str,80,fp) ) lines++;
	rewind(fp);
	num=(int*)malloc(sizeof(int)*lines);
	while(fgets(str,80,fp)){
		num[size]=atoi(str);
		size++;
	}
	
	for(i=0;i<lines;i++){
		printf("[%d]%:%10d  ",i,num[i]);
		if((i+1)%10==0)printf("\n");
	}

	
	quicksort(num,0,size);

	
	/*for(i=0;i<100;i++){
		printf("[%2d]%:%10d ",i,num[i]);
		if((i+1)%10==0)printf("\n");
	}*/

	fclose(fp);

	return 0;
}


