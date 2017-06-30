#include<stdio.h>
/*3j27�c��*/
int max(int x,int y);
int min(int x,int y);
void expand (char data[512] , char pattern[64][64]);
void compress(char data[512],char pattern[64][64]);
void printimg( char data[512] );
void outline( char p[64][64]);
void normalize(char p[64][64]);
void printimg2( char pattern[64][64] );
void smoooth(char p[64][64]);

/*****************************************************************/
int main(){
	char data[512];
	char pattern[64][64];
	int i,j,k;
	int x,y;
	FILE *fp;
	fp=fopen("01.img","rb");
	if (fp==NULL){
		printf("can't open file\n" );
		exit(1);
	}

	//�񎟌��z��Ɋi�[
	expand(data,pattern);
	while(fread(data,512,1,fp) ==1){
		printimg( data ) ;
		expand( data, pattern );
		smoooth(pattern);
		printimg2(pattern);
		

		getchar();	
	}
	fclose(fp);
	return 0;
}


//2�����ׂđ傫���ق���Ԃ�(normalize)**************************************/
int max(int x,int y){
	if(y>x)return y;
	else return x;
}
//2�����ׂď������ق���Ԃ�(normalize)************************************************/
int min(int x,int y){
	if(y>x)return x;
	else return y;
}
/********************************************************/
void expand (char data[512] , char pattern[64][64])
{
	int i,j,k;
	for(k=0; k<64; k++){
		for(j=0;j<8;j++){
			unsigned char b=128;
			for(i=0;i<8;i++){
				if((data[8*k+j] & b)==0){
					pattern[k][8*j+i]=0;
				}else{
					pattern[k][8*j+i]=1;
				}
				b = b>>1;
			}
		}
	}
}
/********************************************************/

void compress(char data[512],char pattern[64][64]){
	int i,j,k;
	unsigned int put;
	for(k=0; k<64; k++){
		for(j=0;j<8;j++){
			data[j+k*8]=0;
			for(i=0;i<8;i++){
				put=pattern[k][j*8+i];
				put=put<<7-i;
				data[k*8+j]+=put;
				
			}
		}
	}
}
/********************************************************/

void printimg( char data[512] )
{
	int k,i,j;
	for(k=0; k<64; k++){
		for(j=0;j<8;j++){
			unsigned char b=128;
			for(i=0;i<8;i++){
				if((data[8 * k +j ] & b)==0){
					printf(".");
				}else{
					printf("*");
				}
				b = b>>1;
			}
		}
		printf("\n");
	}
}
/********************************************************/

void outline( char p[64][64]){
	for (int row = 1; row<63; row++){
		for (int col =1; col<63; col++){
			if(p[row][col]==0)continue;
			if (p[row+1][col]!=0 && p[row-1][col]!=0 && p[row][col+1]!=0 && p[row][col-1]!=0 )p[row][col]=2;
		}
	}
	for (int row = 1; row<63; row++){
		for (int col =1; col<63; col++){
			if(p[row][col]==2)p[row][col]=0;
		}
	}
}
/********************************************************/
/*�g��*/
void normalize(char p[64][64]){
	int i,j,x0=64,y0=64,x1=0,y1=0;
	double W=64,H=64,x,y;
	char p2[64][64];
	for(j=0;j<64;j++){
		for(i=0;i<64;i++){
			if(p[j][i]==1){
				x0=min(x0,i);
				y0=min(y0,j);
				x1=max(x1,i);
				y1=max(y1,j);
			}
		}
	}	
	//printf("x0=%d y0=%d\nx1=%d y1=%d\n",x0,y0,x1,y1);
	double w=x1-x0+1.0;
	double h=y1-y0+1.0;
	//printf("w=%f h=%f\n",w,h);
	
	/*	x0=12  y0= 5
		x1=50  y1=58
		w =39  h =54	*/
	for(j=0;j<64;j++){
		for(i=0;i<64;i++){
			p2[j][i]=p[(int)(j*(h/H)+y0+0.5)][(int)(i*(w/W)+x0+0.5)];

			//	p[j][i]=p[(int)(j*(h/H)+y0+0.5)][(int)(i*(w/W)+x0+0.5)];
		}
	}
	for(j=0;j<64;j++){
		for(i=0;i<64;i++){
			p[j][i]=p2[j][i];
		}
	}
	
}
/****************************************************************/
void printimg2( char pattern[64][64] ){
	int x,y;
	for(y=0;y<64;y++){
		for(x=0;x<64;x++){
			putchar(pattern[y][x] ==1?'@':'.');
		}
		putchar( '\n' ) ;
	}
}

/**********************************************************/
//�X���[�W���O
void smoooth(char pattern[64][64]){
	for (int i=1;i<63;i++){
		for (int j=1;j<63;j++){
			/*�ւ��݂����߂�*/
			if(	pattern[i-1][j-1] &&!pattern[i  ][j-1] && pattern[i+1][j-1] &&
				pattern[i-1][j  ] &&					  pattern[i+1][j  ] &&
				pattern[i-1][j+1] && pattern[i  ][j+1] && pattern[i+1][j+1] ){
				pattern[i][j-1]=1;
			}
			if(  pattern[i-1][j-1] && pattern[i  ][j-1] && pattern[i+1][j-1] &&
				!pattern[i-1][j  ] &&						  pattern[i+1][j  ] &&
				 pattern[i-1][j+1] && pattern[i  ][j+1] && pattern[i+1][j+1] ){
				pattern[i-1][j]=1;
			}
			if(	pattern[i-1][j-1] && pattern[i  ][j-1] && pattern[i+1][j-1] &&
				pattern[i-1][j  ] &&					  pattern[i+1][j  ] &&
				pattern[i-1][j+1] &&!pattern[i  ][j+1] && pattern[i+1][j+1] ){
				pattern[i  ][j+1]=1;
			}
			if(  pattern[i-1][j-1] && pattern[i  ][j-1] &&  pattern[i+1][j-1] &&
				 pattern[i-1][j  ] &&						!pattern[i+1][j  ] &&
				 pattern[i-1][j+1] && pattern[i  ][j+1] &&  pattern[i+1][j+1] ){
				pattern[i+1][j]=1;
			}
			//�ł��ς���Q
			if(	!pattern[i-1][j-1] && pattern[i  ][j-1] && !pattern[i+1][j-1] &&
				pattern[i-1][j  ] &&					 pattern[i+1][j  ] &&
				pattern[i-1][j+1] && pattern[i  ][j+1] && pattern[i+1][j+1] ){
				pattern[i][j-1]=2;
			}
			if( !pattern[i-1][j-1] && pattern[i  ][j-1] && pattern[i+1][j-1] &&
				 pattern[i-1][j  ] &&						 pattern[i+1][j  ] &&
				!pattern[i-1][j+1] && pattern[i  ][j+1] && pattern[i+1][j+1] ){
				pattern[i-1][j]=2;
			}
			if(	pattern[i-1][j-1] && pattern[i  ][j-1] &&!pattern[i+1][j-1] &&
				pattern[i-1][j  ] &&					  pattern[i+1][j  ] &&
				pattern[i-1][j+1] && pattern[i  ][j+1] &&!pattern[i+1][j+1] ){
				pattern[i+1][j]=2;
			}
			if(  pattern[i-1][j-1] && pattern[i  ][j-1] &&  pattern[i+1][j-1] &&
				 pattern[i-1][j  ] &&						   pattern[i+1][j  ] &&
				!pattern[i-1][j+1] && pattern[i  ][j+1] && !pattern[i+1][j+1] ){
				pattern[i][j+1]=2;
			}
			
			for (int i=0;i<63;i++){
				for (int j=0;j<63;j++){
					if(pattern[i][j]==2){
						pattern[i][j]=0;
					}
				}
			}	
		}
	}
	
}
/*void cycle(char a[3][3]){//�E��]
	int num;
	num=a[0][0];
	a[0][0]=a[2][0];
	a[2][0]=num;
	
	num=a[2][0];
	a[2][0]=a[2][2];
	a[2][2]=num;
	
	num=a[2][2];
	a[2][2]=a[0][2];
	a[0][2]=num;

	num=a[0][1];
	a[0][1]=a[1][0];
	a[1][0]=num;
	
	num=a[1][0];
	a[1][0]=a[2][1];
	a[2][1]=num;
	
	num=a[2][1];
	a[2][1]=a[1][2];
	a[1][2]=num;
	
}*/