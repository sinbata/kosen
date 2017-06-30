#include<stdio.h>
/*3j27“c”¨*/
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
	while(fread(data,512,1,fp) ==1){
		printimg( data ) ;
		expand( data, pattern );
		outline(pattern);
		for(y=0;y<64;y++){
			for(x=0;x<64;x++){
				putchar(pattern[y][x] ==1?'@':'o');
			}
			putchar( '\n' ) ;
		}
		

		getchar();	
	}
}