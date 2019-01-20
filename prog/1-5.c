#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>

#define   R       20
#define   N       180
#define   D       196
#define   aiueo   46
#define   M       200

void fileread_mean(double a[D],int Bigroop){
        FILE *fp1;
        char fno1[100];
        double read;
        sprintf(fno1,"mean/mean%02d.txt",Bigroop);
        fp1=fopen(fno1,"r");
	    if(fp1 == NULL) {
		    printf("%s file not open!\n", fno1);
		    return ;
        }
        for(int j=0;j<D;j++){
            if(fscanf(fp1,"%lf",&read) != EOF){
                a[j]=read;
            }
            else {
                printf("ERROR-ave\n");
                return ;
            }
        }
        fclose(fp1);

}
void fileread_vec(double a[D][D],int Bigroop){
        FILE *fp2;
        char fno2[100];
        double read;

        sprintf(fno2,"vec/vec%02d.txt",Bigroop);
        fp2=fopen(fno2,"r");
	    if(fp2 == NULL) {
	        printf("%s file not opendayo!\n", fno2);
            return ;
        }
                //固有ベクトル
        for(int j=0;j<D;j++){
            for(int k=0; k<D;k++){
                if(fscanf(fp2,"%lf",&read) != EOF){
                    a[j][k]=read;
                }
                else {
                    printf("ERROR-vec\n");
                    return ;
                }
            }
        }
        fclose(fp2);
}
void fileread_origin(double a[D],int Bigroop){
        FILE *fp3;
        char fno3[100];
        double read;
        //sprintf(fno3,"/Users/tabataryo/Documents/4J/知識/1-3w/origin/origin%02d.txt",Bigroop);
        sprintf(fno3,"origin/origin%02d.txt",Bigroop);
        fp3=fopen(fno3,"r");
	    if(fp3 == NULL) {
	        printf("%s file not opendayo!\n", fno3);
            return ;
        }
                //固有値
        for(int j=0;j<D;j++){
            if(fscanf(fp3,"%lf",&read) != EOF){
                a[j]=read;
            }
            else {
                printf("ERROR-origin\n");
                return ;
            }
            
        }
        fclose(fp3);
}

void fileread_date(double data[R][D],int Bigroop){
        FILE *fp5;
        char fno5[100];
        double read;
        double a[M][D];
        sprintf(fno5,"data/c%02d.txt",Bigroop);
        fp5=fopen(fno5,"r");
	    if(fp5 == NULL) {
	        printf("%s file not opendayo!\n", fno5);
            return ;
        }
                //求めるdataの読み込み
        for(int j=0;j<M;j++){
            for(int k=0; k<D;k++){
                if(fscanf(fp5,"%lf",&read) != EOF){
                    a[j][k]=read;
                }
                else {
                    printf("ERROR-data\n");
                    return ;
                }
            }
        }
        for(int j=0;j<R;j++){
            for(int k=0;k<D;k++){
                data[j][k] = a[j+N][k];

            }
        }
        fclose(fp5);

}


int main( void ){
    int    i, j, k, m,l, count, status;
    int Bigroop;
    double amax, amax0, theta, co, si, co2, si2, sincos;
    double  pi= 2.0*acos(0.0);
    double aii, aij, ajj, aik, ajk,pik,pjk;  
    char readline[D] = {0};
    double read;
    FILE *fp4;
    FILE *fp5;
    char fno4[100]={0};
    char fno5[100]={0};
    double data[R][D];
    double vectol[D][D];
    double origin[D];
    double ave[D];
    double minave[D];
    double bias=10;
    double dis[aiueo];
    double d;
    double oa[D];
    double MIN_dis=__INT_MAX__;
    double MIN_num;
    double mnum;
    double xm=0;

    for (Bigroop = 1;Bigroop<=aiueo;Bigroop++){
        //ファイル読み込み
        
        sprintf(fno4,"dis/dis%02d.txt",Bigroop);
        fp4=fopen(fno4,"w");
	    if(fp4 == NULL) {
	        printf("%s file not opendayo!\n", fno4);
            return 0;
        }


        //読み込み部分
        fileread_date(data,Bigroop);

        //実行
        count=0;
        for(i=0;i<R;i++){ //２０個のループ
            MIN_dis=__INT_MAX__;
            for(int roop2=1;roop2<=aiueo;roop2++){ //46字種のループ
                //２０個のうちの１つ目の文字持ってくる
                //４６字種のうち求める平均，固有ベクトル，固有値を持ってくる
                fileread_mean(ave,roop2);
                fileread_origin(origin,roop2);
                fileread_vec(vectol,roop2);
                
                xm=0;
                for(k=0;k<D;k++){
                    d=0;
                    for(int o=0;o<D;o++)minave[o] = data[i][o] - ave[o];
                    for(l=0;l<D;l++){
                        //data[i][l] - ave[l] * vectol[l][k] 
                        // / (origin+bias)
                        d += ( minave[l] * vectol[l][k]);
                    }
                    //if(origin[k]>bias)xm += pow(d,2)/(origin[k]);
                    //if(origin[k]<bias)xm += pow(d,2)/(bias);
                    xm += pow(d,2)/(origin[k]+bias);
                }
                
                if(MIN_dis > xm){
                    MIN_dis = xm;
                    MIN_num = roop2;
                    
                }
                //最小距離を更新

            }
            if(MIN_num == Bigroop)count++;
            
        }
        //カウントを20で割って比率を求める
        
        printf("%d : %.3lf\n",Bigroop,(double)count/R);

    }

}

/*
1 : 1.000
2 : 1.000
3 : 0.900
4 : 1.000
5 : 1.000
6 : 1.000
7 : 1.000
8 : 1.000
9 : 1.000
10 : 0.950
11 : 0.950
12 : 1.000
13 : 0.950
14 : 1.000
15 : 1.000
16 : 1.000
17 : 1.000
18 : 0.900
19 : 1.000
20 : 1.000
21 : 1.000
22 : 1.000
23 : 1.000
24 : 0.950
25 : 1.000
26 : 0.950
27 : 0.900
28 : 1.000
29 : 1.000
30 : 1.000
31 : 1.000
32 : 1.000
33 : 1.000
34 : 0.950
35 : 0.900
36 : 0.950
37 : 1.000
38 : 0.950
39 : 0.950
40 : 0.900
41 : 1.000
42 : 1.000
43 : 1.000
44 : 0.950
45 : 0.950
46 : 1.000

*/