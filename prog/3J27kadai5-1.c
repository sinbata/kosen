#include<stdio.h>
#include<stdlib.h>
#define N 10000000
void swap(int *a,int *b)
{
  int temp;
  temp =*a;
  *a=*b;
  *b=temp;
}
/*void quicksort(int d[],int left ,int right)
{

	int pivot,a,b,temp;
	if(left <= right){
		pivot = d[left];
		a=left;
		b=right;
		while(a<=b){
			while(d[a] < pivot)a++;
			while(d[b] > pivot)b--;
			if(a <= b){
				swap(&d[a],&d[b]);
				a++;
				b--;
			}
		}
		quicksort(d, left, b-1);
		quicksort(d, a+1, right);
	}
}

*/
void quickSort(double array[],int sort[], int begin, int end)
{
	int i = begin;
	int j = end;
	double pivot,temp;
	int pivot2,temp2 ;
	
	pivot = array[ ( begin + end ) / 2 ];  // 中央の値をpivotにする
	
	while( 1 )
	{
		while( array[i] < pivot ){ ++i; }  /* 枢軸以上の値が見つかるまで右方向へ進めていく */
		while( array[j] > pivot ){ --j; }  /* 枢軸以下の値が見つかるまで左方向へ進めていく */
		if( i >= j )break;  // 軸がぶつかったらソート終了
		// 入れ替え
		temp = array[i];  temp2 = sort[i];
		array[i] = array[j]; sort[i]=sort[j];
		array[j] = temp;  sort[j]=temp2;
		i++;
		j--;
	}
	
	if( begin < i - 1 ) quickSort( array, sort,begin, i - 1 ); 
	if( j + 1 < end ) quickSort( array, sort,j + 1, end ); 
	}
int main()
{
	FILE *fp;
	FILE *fp2;
	int *d,h=0,size=0,next,lines=0,i=0;
	char str[10];
	
	fp= fopen ("kadai-5-21.txt","r");
	if(fp==NULL){
		printf("file can't open\n");
		exit(1);
	}

	while ( fgets(str,80,fp) ) lines++;
	rewind(fp);
	d=(int*)malloc(sizeof(int)*lines);
	while(fgets(str,80,fp)){
		d[size]=atoi(str);
		size++;
	}
	quicksort(d,0,size-1);
	
	fp2 = fopen("sorted.dat","w");
	if(fp==NULL){
		printf("file can't open\n");
		exit(1);
	}
	for(i=0;i<size;i++){
		fprintf(fp2,"%d\n",d[i]);
		printf("%d",i);
	}
	
	/*for(i=0;i<100;i++){
		printf("[%2d]%:%10d ",i,num[i]);
		if((i+1)%10==0)printf("\n");
	}*/

	fclose(fp);
	fclose(fp2);
	return 0;
}


