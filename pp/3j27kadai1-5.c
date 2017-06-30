/*3j27 1-4*/
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
int cnt=0;
#define N 100

void Insert(int str[],int size){
	int i,j,next;
	for(i=1;i<size; i++){
		next = str[i]; /*next�ɕۑ�*/
		for(j=i; j>=1 && str[j-1] > next; j--){
			str[j]=str[j-1];
			cnt++;
		}
		str[j]=next;
	}
}
void Selective(int str[],int size){
	int i,k,j,tmp;
	for(i=0;i<size;i++){
		k = i;
		for (j = i + 1; j < size; j++) {
			if (str[j] < str[k]) {
				k = j;
			}
		}
		tmp = str[i];
		str[i] = str[k];
		str[k] = tmp;
		cnt++;
	}
}
void Bubble(int str[],int size){
	int tmp,i,j;
	for( int i = size-1 ; 0 < i ; i-- ) {
		for( int j = 0 ; j < i ; j++ ) {
			if(str[j]>str[j+1]){
				tmp=str[j];
				str[j]=str[j+1];
				str[j+1]=tmp;
				cnt++;
			}
		}
	}
}


int main (void){ 
	char filename[50]= {0};
	char fnchange [50]={0};
	char extension[10]={0};
	int num,i,a;
	char n[128];
	int *str;
	int count1=0;
	int size=0,lines=0;
	
	printf("�ǂݍ��݃t�@�C����:");
	scanf("%s",&filename);//�ǂݍ��݃t�@�C��
	FILE *fp;
	FILE *fpw;
	fp= fopen (filename,"r");//�ǂݍ��݃t�@�C��open
	if(fp==NULL){
		printf("can't open the file");
		exit(1);
	}
	while ( fgets(n,80,fp) ) lines++;
	rewind(fp);
	str=(int *)malloc(sizeof(int)*lines);
	for(i=0;i<lines;i++){
		fscanf(fp,"%d",&str[i]);
	}
	
	printf("�������݃t�@�C���̊g���q:");
	scanf("%s",&extension);//�t�@�C�������o���t�@�C���g���q�ǂݍ���
	
	for(int i=0;i<sizeof(filename);i++){
		if(filename[i]=='.'){
			filename[i]='\0';
			break;
		}
	}
	sprintf(fnchange,"%s.%s",filename,extension);//fnchange��filename.extension
	fpw =fopen (fnchange,"w");//�����o���t�@�C��open
	
	printf("�\�[�g���@\n");
	printf("1:�o�u���\�[�g\n");
	printf("2:�I���\�[�g\n");
	printf("3:�}���\�[�g\n");
	scanf("%d",&num);//num  �\�[�g���@
	
	printf("�~����������\n");
	printf("1:�~��\n");
	printf("2:����\n");
	scanf("%d",&a);//str  �~����������

	if(num==1){
		//�o�u���\�[�g
		Bubble(str,lines);
	}
	else if(num==2){
		//�I���\�[�g
		Selective(str,lines);
	}
	else if(num==3){
		//�}���\�[�g
		Insert(str,lines);
	}else {
		return 0;
	}

	if(a==1){
		for (i=lines-1;i>-1;i--){
			fprintf(fpw," %2d", str[i]);
			count1++;
			if(count1%10==0)fprintf(fpw,"\n");
		}
	}	
	else if(a==2){
		for (i=0;i<lines;i++){
			fprintf(fpw," %2d", str[i]);
			count1++;
			if(count1%10==0)fprintf(fpw,"\n");
		}
	}
	fclose(fp);
	fclose(fpw);
	printf("%d",cnt);
	return 0;
}
