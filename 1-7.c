#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include<stdlib.h>
typedef struct{
	double re;
	double im;
}comp;


void fileInN(int num ,char *filename,comp xn_N[]){
   	int i=0;
	FILE *fp;
	fp=fopen(filename,"r");
	if(fp == NULL){
		printf("%s file not open!\n", filename);
	}	
	for(i=0;i<num;i++){
        fscanf(fp,"%lf",&xn_N[i].re);
        xn_N[i].im=0;
        //printf("%lf\n",xn_N[i].re);
    }
	fclose(fp);
}

void fileOutN(int num ,char *filename,comp Xk_N[]){
	int i=0;
	FILE *fp;
	fp=fopen(filename,"w");
	if(fp == NULL) {
		printf("%s file not open!\n", filename);
		return ;
	}
    fprintf(fp,"    real       \n");
	for(i=0;i<num;i++){
		fprintf(fp,"%lf \n",Xk_N[i].re);
	}
    fprintf(fp,"    imag       \n");
	for(i=0;i<num;i++){
		fprintf(fp,"%lf \n",Xk_N[i].im);
	}
	fclose(fp);
}


//足し算
comp comp_add (comp in1 ,comp in2){
	comp result;
	result.re = in1.re + in2.re;
	result.im = in1.im + in2.im;
	return result;
}

//引き算
comp comp_sub (comp in1 ,comp in2){
	comp result;
	result.re = in1.re - in2.re;
	result.im = in1.im - in2.im;
	return result;
}

//かけ算
comp comp_mult (comp in1 ,comp in2){
	comp result;
	result.re = in1.re * in2.re - in1.im * in2.im;
	result.im = in1.re * in2.im + in1.im * in2.re;
	return result;
}

//わり算
comp comp_div (comp in1 ,comp in2){
	comp result;
	result.re = in1.re * in2.re;
	result.im = in1.im * in2.im;
	return result;
}

//共役複素数
comp conjugate(comp conj){
	comp result;
	result.re = conj.re;
	result.im = conj.im * -1;
	return result;
}
//回転子

void twid(comp *wnk,  int num){
	double pi =acos(-1);
    double omega = 2*pi/(double)num;
	int i,j=0;
	
    for(i=0;i<num/2;i++){
		wnk[i].re = cos(omega * (double)i);//回転子の値
		wnk[i].im = -1*sin(omega * (double)i);
	}
	//for(int i=0;i<num/2;i++) printf("%lf   %lf\n",wnk[i].re,wnk[i].im);
}

void bitRev(int br[],int num){
	
	double step = log((double)num)/log(2.0);
	br[0]=0;
	int roop=1;
	for(int i=0;i<step;i++){
		for(int j=0;j<roop;j++){
			br[roop+j]=br[j]+num/(2*roop);
		}
		roop *= 2;	
	}
}
void butterfly(comp in1,comp in2,comp *out,comp *wnk,int a,int num){
	comp rev = wnk[a];
	if(num/2 < a){
		rev = conjugate(wnk[a]);
		out[0] = comp_add(in1,comp_mult(in2,rev));
		out[1] = comp_sub(in1,comp_mult(in2,rev));
	}else{
		out[0] = comp_add(in1,comp_mult(in2,rev));
		out[1] = comp_sub(in1,comp_mult(in2,rev));
	}
}
void fft(comp *in,int num){//in 配列   wnk　回転子   num 要素数   
	clock_t start=0, stop=0;
    double diff;
	start = time(NULL);
	comp out[2];//バタフライ用
	comp wnk[num/2];
	int roopBig = 1,roopSmall = num / 2;
	double r = log((double)num)/log(2.0);
	int in1,in2;
	int br[num];
	for(int i=0;i<num;i++)br[i]=i;
	twid(wnk,num);
	bitRev(br,num);
	comp buf;
	for(int i=0;i<num/2;i++){
		buf = in[i];
		in[i] = in[br[i]];
		in[br[i]] = buf;
	}
	//for(int i=0;i<num;i++)printf("%lf \n",in[i].re);
	for(int i=0;i<r;i++){
		//int bias=0;
		for(int j=0;j<roopBig;j++){
			for(int k=0;k<roopSmall;k++){
				in1 = 2 * roopBig * k + j;
				in2 = in1 + roopBig;
				butterfly(in[in1],in[in2],out,wnk,j*roopSmall,num);
				in[in1] = out[0];
				in[in2] = out[1];
			}
			//bias += roopBig * 2;
		}
		roopSmall /=2;
		roopBig *= 2;
	}
	stop = time(NULL);
	diff = difftime(stop, start);
	printf("動作時間：%f\n",diff);
}
int main()
{


	clock_t start=0, stop=0;
    double diff;
	int number=0;
	char filename_in[100];
	char filename_out[100];
	printf("入力ファイル名 → ");
	scanf("%s",&filename_in);
	printf("出力ファイル名 → ");
	scanf("%s",&filename_out);
	printf("要素数 → ");
	scanf("%d",&number);

	comp xn[number];
	fileInN(number,filename_in,xn);
	for(int i=0;i<number;i++) printf("%10lf %10lf\n",xn[i].re,xn[i].im);
	start = time(NULL);
	fft(xn,number);
	stop = time(NULL);
	fileOutN(number,filename_out,xn);
	diff = difftime(stop, start);
	//printf("動作時間：%f\n %f\n %f\n",stop,start,diff);
	//for(int i=0;i<number;i++) printf("%10lf %10lf\n",xn[i].re,xn[i].im);
	return 0;
}


