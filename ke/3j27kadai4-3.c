#include<stdio.h>
#define DIM   64
#define H 64
#define W 64
/*3j27“c”¨*/
int  max(int x,int y);
int  min(int x,int y);
void expand (char data[512] , char pattern[64][64]);
void compress(char data[512],char pattern[64][64]);
void printimg( char data[512] );
void outline( char p[64][64]);
void normalize(char p[64][64]);
void reLabel (char p[64][64],int x,int y,int now);
int  label (char p[64][64]);
void noise(char p[64][64] ,int size);
#define debug printf("%d %s ",__LINE__,__func__); printf
void smoooth(char pattern[64][64]);
void extract( char p[64][64], int f[DIM] );
void printimg2( char pattern[64][64] );

/*****************************************************************/
int main(){
	char data[512];
	char pattern[64][64];
    FILE    *fp1, *fp2 ;
    char    infn[0x80], outfn[0x80] ;
    char    img[512] ;
    char    p[64][64] ;
    int     f[DIM] ;
    int     num, i, j ;


	for( i = 0 ; i < 46 ; i++ ) {
		sprintf( infn, "%02d.img", i+1 ) ;
		sprintf( outfn, "%02d.ftr", i+1 ) ;
	
		fp1 = fopen( infn, "rb" ) ;
		fp2 = fopen( outfn, "w" ) ;
	//“ñŽŸŒ³”z—ñ‚ÉŠi”[
		while(fread(data,512,1,fp1) ==1){
			expand( data, pattern );
			noise(pattern , 10);
			smoooth(pattern);
			normalize(pattern);
			outline(pattern);
			extract(pattern , f);
			for( j = 0 ; j < DIM ; j++ ) {
				fprintf( fp2, "%d\n", f[j] ) ;
			}
			/*for( j = 0 ; j < DIM ; j++ ) {
				printf(" %2d", f[j] ) ;
			}*/
			printf("\n");
		}
		fclose( fp1 ) ;
		fclose( fp2 ) ;
	}
}

void extract( char p[64][64], int f[DIM] ){
	int i,j,x,y;
	int count=0;
	for(i=0;i<DIM;i++){
		f[i]=0;
	}
	for(i=0;i<64;i+=16){
		for(j=0;j<64;j+=16){
			for(y=i;y<i+16;y++){
				for(x=j;x<j+16;x++){
					/*if (p[y][x]==1 && p[y  ][x-1]==1 && p[y  ][x+1]==1)f[count * 4   ]++;
					if (p[y][x]==1 && p[y-1][x  ]==1 && p[y+1][x  ]==1)f[count * 4 +1]++;
					if (p[y][x]==1 && p[y-1][x+1]==1 && p[y+1][x-1]==1)f[count * 4 +2]++;
					if (p[y][x]==1 && p[y-1][x-1]==1 && p[y+1][x+1]==1)f[count * 4 +3]++;*/
					if(p[y][x]==1 && p[y-1][x  ]==1 )f[count *4   ]++;
					if(p[y][x]==1 && p[y+1][x  ]==1 )f[count *4   ]++;
					if(p[y][x]==1 && p[y  ][x-1]==1 )f[count *4 +1]++;
					if(p[y][x]==1 && p[y  ][x+1]==1 )f[count *4 +1]++;
					if(p[y][x]==1 && p[y-1][x+1]==1 )f[count *4 +2]++;
					if(p[y][x]==1 && p[y+1][x-1]==1 )f[count *4 +2]++;
					if(p[y][x]==1 && p[y-1][x-1]==1 )f[count *4 +3]++;
					if(p[y][x]==1 && p[y+1][x+1]==1 )f[count *4 +3]++;
				}
					
			}
			count++;
		}
	}

}
void printimg2( char pattern[64][64] ){
	int x,y;
	for(y=0;y<64;y++){
		for(x=0;x<64;x++){
			if(pattern[y][x]==0)printf(".");
			if(pattern[y][x]==1)printf("*");
		}
		putchar( '\n' ) ;
	}
}
//2”‚ð”ä‚×‚Ä‘å‚«‚¢‚Ù‚¤‚ð•Ô‚·(normalize)**************************************/
int max(int x,int y){
	if(y>x)return y;
	else return x;
}
//2”‚ð”ä‚×‚Ä¬‚³‚¢‚Ù‚¤‚ð•Ô‚·(normalize)************************************************/
int min(int x,int y){
	if(y>x)return x;
	else return y;
}
/********************************************************/
void expand(char data[512],char pattern[64][64]){
	for(int i=0;i<512;i++){
		for(int j=7;j>=0;j--){
			if(data[i]&(1<<j)){
				pattern[i/8][(i%8+1)*8-j]=1;
			}else{
				pattern[i/8][(i%8+1)*8-j]=0;
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
	printf("\n");
}
/********************************************************/

void outlines(char pattern[64][64]){
	for(int i=1;i<64-1;i++){
		for(int j=1;j<64-1;j++){
			if(	pattern[i-1][j-1] && pattern[i  ][j-1] && pattern[i+1][j-1] &&
				pattern[i-1][j  ] &&					  pattern[i+1][j  ] &&
				pattern[i-1][j+1] && pattern[i  ][j+1] && pattern[i+1][j+1] ){
				pattern[i][j]=2;
			}
		}
	}
	for(int i=1;i<64-1;i++){
		for(int j=1;j<64-1;j++){
			if(pattern[i][j]==2){
				pattern[i][j]=0;
			}
		}
	}
}

/********************************************************/
/*Šg‘å*/
void normalize(char p[H][W])
{
	int i,j;
	double x0=H,y0=W,w=0.0,h=0.0;
	char p2[H][W];
	memset(p2,0,sizeof(p2));
	
	for (i=0;i<H;i++){
		for(j=0;j<W;j++){
			if(p[i][j]==1 && j<x0) x0=j;
			if(p[i][j]==1 && j>w) w=j;
			if(p[j][i]==1 && j<y0) y0=j;
			if(p[j][i]==1 && j>h) h=j;
		}
	}
	w=w-x0+1.0;
	h=h-y0+1.0;
	
	for(j=0;j<H;j++){
		for(i=0;i<W;i++){
			p2[j][i]=p[(int)((j)*(h/H)+y0+0.5)][(int)((i)*(w/W)+x0+0.5)];
		}
	}
	printf("\n");
	for(j=0;j<H;j++){
		for(i=0;i<W;i++){
			p[j][i]=p2[j][i];
		}
	}
	
}
/****************************************************************/


//ƒXƒ€[ƒWƒ“ƒO
void smoooth(char pattern[64][64]){
	for (int i=1;i<63;i++){
		for (int j=1;j<63;j++){
			/*‚Ö‚±‚Ý‚ð‚¤‚ß‚é*/
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
			//‚Å‚Á‚Ï‚è‚ð‚Q
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
	
}/*************************************************************************************
/******************************************************************/
//ƒmƒCƒYœ‹Ž label

void LabelSearch(char p[H][W],int labelnum,int h,int w)
{
	int i;
	p[h][w]=labelnum;
	if  (p[h][w+1]==1) LabelSearch(p,labelnum,h,w+1);
	if  (p[h+1][w]==1) LabelSearch(p,labelnum,h+1,w);
	if  (p[h][w-1]==1) LabelSearch(p,labelnum,h,w-1);
	if  (p[h-1][w]==1) LabelSearch(p,labelnum,h-1,w);
}


int label(char p[H][W]){

	int labelnum=2;
	for(int i=0;i<H;i++){
		for(int j=0;j<W;j++){
			if(p[i][j]==1){
				LabelSearch(p,labelnum,i,j);
				labelnum++;
				if(labelnum>=255) return 1;
			}
		}
	}
	return 0;
}



void noise(char p[H][W],int size){

	for(int labelnum=2;labelnum<255;labelnum++){
		int noisesize=0;
		for(int i=0;i<H;i++){
			for(int j=0;j<W;j++){
				if(p[i][j]==labelnum) noisesize++;
			}
		}
		if(noisesize<size){
			for(int i=0;i<H;i++){
				for(int j=0;j<W;j++){
					if(p[i][j]==labelnum) p[i][j]=0;
				}
			}
		}
	}
	for(int i=0;i<H;i++){
		for(int j=0;j<W;j++){
			if(p[i][j]!=0) p[i][j]=1;
		}
	}



}

void outline(char pattern[64][64]){
	for(int i=1;i<64-1;i++){
		for(int j=1;j<64-1;j++){
			if(	pattern[i-1][j-1] && pattern[i  ][j-1] && pattern[i+1][j-1] &&
				pattern[i-1][j  ] &&					  pattern[i+1][j  ] &&
				pattern[i-1][j+1] && pattern[i  ][j+1] && pattern[i+1][j+1] ){
				pattern[i][j]=2;
			}
		}
	}
	for(int i=1;i<64-1;i++){
		for(int j=1;j<64-1;j++){
			if(pattern[i][j]==2){
				pattern[i][j]=0;
			}
		}
	}
}