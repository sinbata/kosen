/*4H27田畑凌　課題1-1*/
#include<stdio.h>
#include<stdlib.h>

#define ALL 200
#define N 180
#define D 196
#define aiueo 46

void Fileopen(FILE *fp,char filename[]){
    fp=fopen(filename,"r");
	if(fp == NULL) {
		printf("%s file not open!\n", filename);
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
        sprintf(fni,"data/c%02d.txt",i);
        fp1=fopen(fni,"r");
	    if(fp1 == NULL) {
		    printf("%s file not open!\n", fni);
		    return ;
        }
        sprintf(fno,"mean/mean%02d.txt",i);
            fp2=fopen(fno,"w");
	        if(fp2 == NULL) {
		        printf("%s file not opendayo!\n", fno);
		        return ;
        }
            for(int k=0;k<N;k++){
                for(int l=0;l<D;l++){
                    fscanf(fp1,"%lf",&buf);
                    str[l]+=buf;
                }
            }

        for(int j=0;j<D;j++){
            Ave[j]=str[j]/N;
            fprintf(fp2,"%f\n",Ave[j]);
        }
        
        //printf("%d\n",i);
        for(int j=0;j<D;j++){
            str[j]=0.0;
        }
    }
}
int main (){
    average();
}
