/*4H27�c�����@�ۑ�1-2*/
#include<stdio.h>
#include<stdlib.h>

#define ALL 200
#define N 180
#define D 196
#define aiueo 46

void Fileopen(FILE *fp,char filename[]){
    fp=fopen(filename,"r");
	if(fp == NULL) {
		printf("%s file not open!�_n", filename);
		return ;
    }
}
void average(){
    FILE *fp1;
    FILE *fp2;

    char fni[100];
    char fno[100];
    double str[D]={0};
    double Ave[N]={0};
    double buf;
    for (int i =1;i<aiueo+1;i++){
        sprintf(fni,"/Users/tabataryo/Documents/4J/�m��/1-1/�ۑ�f�[�^/c%02d.txt",i);
        fp1=fopen(fni,"r");
	    if(fp1 == NULL) {
		    printf("%s file not open!aaaa�_n", fni);
		    return ;
        }
        sprintf(fno,"/Users/tabataryo/Documents/4J/�m��/1-1/mean/mean%02d.txt",i);
            fp2=fopen(fno,"w");
	        if(fp2 == NULL) {
		        printf("%s file not opendayo!�_n", fno);
		        return ;
        }
            for(int k=0;k<N;k++){
                for(int l=0;l<D;l++){
                fscanf(fp1,"%lf",&buf);
                str[l]+=buf;
                }
            }

        for(int j=0;j<N;j++){
            Ave[j]=str[j]/N;
            fprintf(fp2,"%f�_n",Ave[j]);
        }
        printf("%d�_n",i);
    }
}
void dispersion(){
    FILE *fp1;
    FILE *fp2;
    FILE *fp3;
    int i,j,k,l;
    char fni[100];
    char fno[100];
    char fin[100];
    double mave[D]={0};
    double cstr[N][N]={0};
    double dis[D][D]={0};
    double buf;
    double Ave[D]={0};
    double str[D]={0};
    for (i =1;i<aiueo+1;i++){
        sprintf(fin,"/Users/tabataryo/Documents/4J/�m��/1-1/�ۑ�f�[�^/c%02d.txt",i);
        fp3=fopen(fin,"r");
	    if(fp3 == NULL) {
		    printf("%s file not open!�_n", fin);
		    return ;
        }
        sprintf(fni,"/Users/tabataryo/Documents/4J/�m��/1-1/mean/mean%02d.txt",i);
        fp1=fopen(fni,"r");
	    if(fp1 == NULL) {
		    printf("%s file not open!�_n", fni);
		    return ;
        }
        sprintf(fno,"/Users/tabataryo/Documents/4J/�m��/1-1/sigma/sigma%02d.txt",i);
            fp2=fopen(fno,"w");
	        if(fp2 == NULL) {
		        printf("%s file not opendayo!�_n", fno);
		        return ;
        }
        for(j=0;j<N;j++){
            for(k=0;k<D;k++){
                fscanf(fp3,"%lf",&buf);//�ۑ�f�[�^����ǂݍ���
                cstr[j][k]=buf;
            }
        }
        for(j=0;j<D;j++){
            fscanf(fp1,"%lf",&buf);//���ς���ǂݍ���
            mave[j]=buf;
        }
        
        for(k=0;k<D;k++){//�����U�̃��[�v
            for(l=0;l<D;l++){ //�����U�̃��[��
                for(j=0;j<N;j++){//�V�O�}��0->180���[�v�@
                    dis[k][l] +=  (cstr[j][k]-mave[k])*(cstr[j][l]-mave[l]);
                }
            } 
        }
        for(int o=0;o<D;o++){
            for(int p=0;p<D;p++){
                dis[o][p] /= N;
                fprintf(fp2,"%15f ",dis[o][p]);
            }
            fprintf(fp2,"�_n");  
        }    
        //printf("%d�_n",i);
    }
}
int main (){
    dispersion();
}
