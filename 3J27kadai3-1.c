#include<stdio.h>
#include<stdlib.h>

#define N 100


int main()
{
	int num[N];
	int i=0,j,h=1,k=0,next;
	
	FILE *fp;
	fp=fopen("kadai-1-3.txt","r");
	if (fp ==NULL){
		printf("can't open file\n");
		exit(1);
	}
	while(fscanf(fp,"%d",&num[i])==1)	i++;
	
	while(h<=N) h=3*h+1;
	printf("%d\n",h);
	
	while(h>0){
		h=h/3;
		for(k=0;k<h;k++){
			for(i=h+k;i<N;i+=h){
				next=num[i];
				for(j=i; j>=h && num[j-h]>next; j-=h){
					num[j]=num[j-h];	
				}
				num[j]=next;
			}
		}
	}
	for(i=0;i<N;i++){
		printf(" %2d",num[i]);
		if((i+1)%10==0)printf("\n");
	}

	fclose(fp);

	return 0;
}