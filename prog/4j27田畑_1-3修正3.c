#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define   TOL     0.001
#define   N       180
#define   D       196
#define   aiueo   46

void quicksort(double array[],int begin, int end)
{
	int i = begin;
	int j = end;
	double pivot,temp;

	
	pivot = array[ ( begin + end ) / 2 ];  // 中央の値をpivotにする
	
	while( 1 ){
		while( array[i] > pivot ) ++i;   /* 枢軸以上の値が見つかるまで右方向へ進めていく */
		while( array[j] < pivot ) --j;   /* 枢軸以下の値が見つかるまで左方向へ進めていく */
		if( i >= j )break;  // 軸がぶつかったらソート終了

		temp = array[i];  
		array[i] = array[j]; 
		array[j] = temp;  
		i++;
		j--;
	}
	
	if( begin < i - 1 ) quicksort( array,begin, i - 1 ); 
	if( j + 1 < end ) quicksort( array,j + 1, end ); 
}

void bubbleSort(double psorted[D][D],double a[])
{
  int i, j, k;

  double tmp[D],temp;

  for (i = 0; i < (D - 1); i++) {
    for (j = D - 1; j > i; j--) {
      if (a[j-1] > a[j]) {
            temp = a[j-1];
            a[j-1] = a[j];
            a[j] = a[j-1];

            for(k=0;k<D;k++){
                tmp[k] = psorted[k][j];
                psorted[k][j]=psorted[k][j-1];
                psorted[k][j-1]=tmp[j];
            }
        }
    }
  }
}

void sortchange(int sort[],double a[],double sort_buf[]){
    for(int i=0;i<D/2;i++){
        for(int j=0;j<D;j++){
            if(a[j] == sort_buf[i]){
                sort[i]=j;
            }
        }
    }
}


void sortD (double psorted[D][D],int sort[D]){
    double tmp[D];
    for(int i=0;i<D/2;i++){
        for(int j=0;j<D;j++){

        }

    }

}
void tenti(double a[D][D]){
    double out[D][D];
    for(int i=0;i<D;i++){
        for(int j=0;j<D;j++){
            out[j][i] = a[i][j];
        }
    }
    for(int i=0;i<D;i++){
        for(int j=0;j<D;j++){
            a[i][j] = out[i][j];
        }
    }


}
int main( void ){
    int    i, j, k, m, count, status;
    int Bigroop;
    double amax, amax0, theta, co, si, co2, si2, sincos;
    double  pi= 2.0*acos(0.0);
    double aii, aij, ajj, aik, ajk,pik,pjk;  
    char readline[D] = {0};
    double read;
    FILE *fp1;
    FILE *fp2;
    FILE *fp3;
    FILE *fp4;
    char fni[100]={0};
    char fno[100]={0};
    char fno3[100]={0};
    char fno4[100]={0};
    double a[D][D];

    double p[D][D];
    int sort[D];
    double sorta[D];
    double out[D][D];
    double sort_buf[D];


    for (Bigroop =1;Bigroop<=aiueo;Bigroop++){
        //ファイル読み込み
        //sprintf(fni,"/Users/tabataryo/Documents/4J/知識/1-3w/sigma/sigma%02d.txt",Bigroop);
        sprintf(fni,"sigma/sigma%02d.txt",Bigroop);
        fp1=fopen(fni,"r");
	    if(fp1 == NULL) {
		    printf("%s file not open!\n", fni);
		    return 0;
        }
        //sprintf(fno,"/Users/tabataryo/Documents/4J/知識/1-3w/vec/vec%02d.txt",Bigroop);
        sprintf(fno,"vec/vec%02d.txt",Bigroop);
        fp2=fopen(fno,"w");
	    if(fp2 == NULL) {
	        printf("%s file not opendayo!\n", fno);
            return 0;
        }
        //sprintf(fno3,"/Users/tabataryo/Documents/4J/知識/1-3w/origin/origin%02d.txt",Bigroop);
        sprintf(fno3,"origin/origin%02d.txt",Bigroop);
        fp3=fopen(fno3,"w");
	    if(fp3 == NULL) {
	        printf("%s file not opendayo!\n", fno3);
            return 0;
        }
        //sprintf(fno4,"/Users/tabataryo/Documents/4J/知識/1-3w/test/test%02d.txt",Bigroop);
        sprintf(fno4,"test/test%02d.txt",Bigroop);
        fp4=fopen(fno4,"w");
	    if(fp4 == NULL) {
	        printf("%s file not opendayo!\n", fno4);
            return 0;
        }
        //読み込み部分
        
        for(j=0;j<D;j++){
            for(k=0; k<D;k++){
                if(fscanf(fp1,"%lf",&read) != EOF){
                    a[j][k]=read;
                }
                else {
                    printf("ERROR\n");
                    return 0;
                }
            }
        }
        
        //   初期値設定
        for(i=0; i<D; i++){
            for(j=0; j<D; j++){
                if( i == j ) p[i][j] = 1.0; 
                else p[i][j] = 0.0;
            }
        }

        //   反復計算
        count=0;
        do
        {
            //  非対角要素の最大値を探索
            amax = 0.0;
            for(k=0; k<D-1; k++){
                for(m=k+1; m<D; m++){
                    amax0 = fabs( a[k][m] );
                    if( amax0 > amax )  { 
                        i = k;  
                        j = m,  
                        amax = amax0; 
                    }
                }
            }
            aii = a[i][i];   
            aij = a[i][j];   
            ajj = a[j][j];
            //   回転角度計算
            if( fabs(ajj-aii) < TOL ){
                if(aij<0.0)theta = -0.25*pi;
                else theta = 0.25*pi;
            }else{
                theta = 0.50*atan(2.0*aij/(ajj-aii));
            }
            co = cos(theta); 
            si = sin(theta); 

            for(k=0; k<D; k++){// A * P
                aik = a[k][i];   
                ajk = a[k][j];
                a[k][i] = co*aik - si*ajk;  
                a[k][j] = si*aik + co*ajk;
                pik = p[k][i];
                pjk = p[k][j];
                p[k][i] = co * pik - si * pjk;
                p[k][j] = si * pik + co * pjk;    

            }
            for(k=0; k<D; k++){//p-1 * A
                aik = a[i][k];
                ajk = a[j][k];
                a[i][k] = co*aik - si*ajk;  
                a[j][k] = si*aik + co*ajk;
            }


            count++;
            //printf("unko%d  %f\n",count,amax);
        }while(amax >= TOL);
        for(k=0;k<D;k++)sort[k]=k;
        for(k=0;k<D;k++){
            sorta[k]=a[k][k];
            sort_buf[k]=a[k][k];
        }
        /*
        quicksort(sorta,0,D-1);
        sortchange(sort,sorta,sort_buf);
        sortD(p,sort);
        */
       bubbleSort(p,sorta);
        
        //for(k=0; k<D; k++)  fprintf(fp4," %d \n",sort[k]);//固有値
        for(k=0; k<D; k++)  fprintf(fp3," %10.6f \n",sorta[k]);//固有値
        for(j=0;j<D;j++){//固有ベクト
            for(k=0;k<D;k++)fprintf(fp2,"%10.6f ",p[j][k]);
            fprintf(fp2,"\n");
        }
        printf("%2d complete.\n",Bigroop);
    }
}

