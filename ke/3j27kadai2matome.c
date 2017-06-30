#include<stdio.h>
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

void expand (char data[512] , char pattern[64][64])
{
	int i,j,k;
	for(k=0; k<64; k++){
		for(j=0;j<8;j++){
			unsigned char b=128;
			for(i=0;i<8;i++){
				if((data[8*k+j] & b)==0){
					pattern[k][8*j+i]=1;
				}else{
					pattern[k][8*j+i]=0;
				}
				b = b>>1;
			}
		}
	}
}

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
		expand( data, pattern ) ;
		for(y=0;y<64;y++){
			for(x=0;x<64;x++){
				putchar(pattern[y][x] ==1?'@':'o');
			}
			putchar( '\n' ) ;
		}
		compress( data, pattern );
		printimg( data ) ;
		getchar();
	}
	fclose(fp);
	return 0;
}
