/*4H27田畑凌　課題1-2*/
#include<stdio.h>
#include<stdlib.h>

#define ALL 200
#define N 180
#define D 196
#define aiueo 46

void Fileopen(FILE *fp,char filename[]){
    fp=fopen(filename,"r");
	if(fp == NULL) {
		printf("%s file not open!＼n", filename);
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
        sprintf(fni,"/Users/tabataryo/Documents/4J/知識/1-1/課題データ/c%02d.txt",i);
        fp1=fopen(fni,"r");
	    if(fp1 == NULL) {
		    printf("%s file not open!aaaa＼n", fni);
		    return ;
        }
        sprintf(fno,"/Users/tabataryo/Documents/4J/知識/1-1/mean/mean%02d.txt",i);
            fp2=fopen(fno,"w");
	        if(fp2 == NULL) {
		        printf("%s file not opendayo!＼n", fno);
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
            fprintf(fp2,"%f＼n",Ave[j]);
        }
        printf("%d＼n",i);
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
    double cstr[N][D]={0};
    double dis[D][D]={0};
    double buf;
    double Ave[D]={0};
    double str[D]={0};
    for (i =1;i<aiueo+1;i++){
        //sprintf(fin,"/Users/tabataryo/Documents/4J/知識/1-1/課題データ/c%02d.txt",i);
        sprintf(fin,"data/c%02d.txt",i);
        fp3=fopen(fin,"r");
	    if(fp3 == NULL) {
		    printf("%s file not open!＼n", fin);
		    return ;
        }
        //sprintf(fni,"/Users/tabataryo/Documents/4J/知識/1-1/mean/mean%02d.txt",i);
        sprintf(fni,"mean/mean%02d.txt",i);
        fp1=fopen(fni,"r");
	    if(fp1 == NULL) {
		    printf("%s file not open!＼n", fni);
		    return ;
        }
        //sprintf(fno,"/Users/tabataryo/Documents/4J/知識/1-1/sigma/sigma%02d.txt",i);
        sprintf(fno,"sigma/sigma%02d.txt",i);
            fp2=fopen(fno,"w");
	        if(fp2 == NULL) {
		        printf("%s file not opendayo!＼n", fno);
		        return ;
        }
        for(j=0;j<N;j++){
            for(k=0;k<D;k++){
                fscanf(fp3,"%lf",&buf);//課題データから読み込み
                cstr[j][k]=buf;
            }
        }
        for(j=0;j<D;j++){
            fscanf(fp1,"%lf",&buf);//平均から読み込み
            mave[j]=buf;
        }
        for(k=0;k<D;k++){
            for(j=0;j<D;j++){
                dis[k][j]=0.0;
            }
        }

        for(k=0;k<D;k++){//共分散のループ
            for(l=0;l<D;l++){ //共分散のルーぷ
                for(j=0;j<N;j++){//シグマの0->180ループ　
                    dis[k][l] +=  (cstr[j][k]-mave[k])*(cstr[j][l]-mave[l]);
                }
                dis[k][l] = dis[k][l]/N;
            } 
        }
        for(int o=0;o<D;o++){
            for(int p=0;p<D;p++){
                fprintf(fp2,"%f ",dis[o][p]);
            }
            fprintf(fp2,"\n");  
        }    
        //printf("%d\n",i);
    }
}
int main (){
    dispersion();
}
