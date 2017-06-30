#include<stdio.h>
#include<stdlib.h>
void quicksort (int d[], int a, int b);
#define N 10000000
int main()
{
	int lines=0;
	int num[N];
	int i=0,j,h=1,k=0,next;
	int *str;
	int count=0;
	FILE *fp;
	fp= fopen ("kadai5-1","r");//i≪C?cuC?EtE@ECEaopen
	if(fp==NULL){
		printf("can't open the file");
		exit(1);
	}
	
	while (!feof(fp) && num <N){
		fscanf(fp, "%d", &(num[lines]));
		lines++;
	}
	rewind(fp);
	str=(int *)malloc(sizeof(int)*lines);
	for(i=0;i<lines;i++){
		fscanf(fp,"%d",&str[i]);
	}
	quicksort(str,0,lines);

	
	for(i=0;i<N;i++){
		printf(" %2d",num[i]);
		if((i+1)%10==0)printf("\n");
	}

	fclose(fp);

	return 0;
}

void quicksort (int d[], int a, int b){
	int size=sizeof(d) / sizeof(int);
	if(size==1)return;
	int temp;
	int pivot;
	int last=b;
	int start=a;
	pivot = d[a];
	
	while (1){
		if(d[a]<pivot)a++;
		if(d[b]>pivot)b--;
		if(a>b){
			temp=d[a];
			d[a]=d[b];
			d[b]=temp;
			break;
		}
		if(a==b){
			temp=d[a];
			d[a]=pivot;
			pivot=d[a];
		}
		quicksort(d,start,a);
		quicksort(d,a,last);
	}

}
