#include <stdio.h>
#include <math.h>

#define n 3                             //未知数の個数
#define max 100                 //繰り返し最大回数
#define eps 1.0e-5              //最小誤差許容範囲


/*********  固有値をJacobi法による求める副関数  ************************/
/*   戻り値（エラーコード）：  0=正常,      9: 異常                    */
/*   入力： a[n×n]=行列，  n: 要素数                                  */
/*   出力： 固有値（解）は a の対角要素                                */
/*          固有ベクトルは x[n×n]                                     */
/************************************************************************/


int main()
{
        int i,j,k;
        double err;
/*配列a,bには係数の値等を。配列xoldには適当に決めた解の値を入れておく*/
        double a[n][n]={{3.0,-6.0,9.0},{2.0,5.0,-8.0},{1.0,-4.0,7.0}},
                b[n]={6.0,8.0,2.0},xold[n]={1.0,1.0,1.0},xnew[n];

        for(k=0;k<max;k++) {
                err=0.0;                        //誤差のリセット
                for(i=0;i<n;i++) {
                        xnew[i]=b[i];
                        for(j=0;j<n;j++) {
                                if(j!=i) {
                                        xnew[i]-=a[i][j]*xold[j];
                                }
                        }
                        xnew[i]=xnew[i]/a[i][i];
                }

/*各解の誤差を足し、古い解は捨て配列xoldに新しい解を入れる*/
                for(i=0;i<n;i++) {
                        err+=fabs(xold[i]-xnew[i]);
                        xold[i]=xnew[i];
                }

/*足しあわされた誤差が許容範囲内だったら
計算終了とし解が求まったとする*/
                if(err<eps) break;
        }

/*求まった解を出力する*/
        for(i=0;i<n;i++) {
                printf("%8.4f\n",xnew[i]);
        }

/*繰り返し回数が最大回数の値だったら
正確な解が求まっていない可能性大なので注意*/
        printf("繰り返し回数は %d\n",k+1);

        return 0;
}
