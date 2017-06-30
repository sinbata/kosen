//
//  main.c
//  3j27kadai3-2
//
//  Created by 田畑　凌 on 2017/06/06.
//  Copyright c 2017年 田畑　凌. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    //char filename[50]= {0};
    //char fnchange [50]={0};
    //char extension[10]={0};
    int i,k,j;
    int *str;
    int lines=0;
    int next;
    int count=0;
    int h=0;
    char n[10000]={0};
    int count1=0;
    int count2=0;
    int str2[100000];
    /*printf("読み込みファイル名:");
     scanf("%s",filename);//読み込みファイル
     FILE *fp;
     FILE *fpw;
     fp= fopen (filename,"r");//読み込みファイルopen
     if(fp==NULL){
     printf("can't open the file");
     exit(1);
     }
     while ( fgets(n ,80,fp) ) lines++;
     rewind(fp);
     str=(int *)malloc(sizeof(int)*lines);
     for(i=0;i<lines;i++){
     fscanf(fp,"%d",&str[i]);
     }
     
     printf("書き込みファイルの拡張子:");
     scanf("%s",extension);//ファイル書き出しファイル拡張子読み込み
     
     for(int i=0;i<sizeof(filename);i++){
     if(filename[i]=='.'){
     filename[i]='\0';
     break;
     }
     }
     fclose(fp);
     sprintf(fnchange,"%s.%s",filename,extension);//fnchangeはfilename.extension
     fpw =fopen (fnchange,"w");//書き出しファイルopen
     */
    FILE *fp;
    fp=fopen("kadai15.txt","r");
    if (fp ==NULL){
        printf("can't open file\n");
        exit(1);
    }
    while ( fgets(n,80,fp) ) lines++;
    rewind(fp);
    str=(int *)malloc(sizeof(int)*lines);
    for(i=0;i<lines;i++){
        fscanf(fp,"%d",&str[i]);
    }
    for(i=0;i<lines;i++){
        str2[i]=str[i];
    }
    fclose(fp);
    while(h<=lines) h=3*h+1;
    printf("%d\n",h);
    
    while(h>0){
        h=h/3;
        for(k=0;k<h;k++){
            for(i=h+k;i<lines;i+=h){
                next=str[i];
                for(j=i; j>=h && str[j-h]>next; j-=h){
                    str[j]=str[j-h];
                    count++;
                }
                str[j]=next;
            }
        }
    }//shell
    
    for(i=1;i<lines; i++){
        next = str2[i]; /*nextに保存*/
        for(j=i; j>=1 && str2[j-1] > next; j--){
            str2[j]=str2[j-1];
            count2++;
        }
        str2[j]=next;
    }
    
    
    for(i=0;i<lines;i++){
        printf("  %2d",str[i]);
        count1++;
        if(count1%10==0)printf("\n");
    }
    printf("\n\n");
    count1=0;
    for(i=0;i<lines;i++){
        printf("  %2d",str2[i]);
        count1++;
        if(count1%10==0)printf("\n");
    }
    printf("\n\n");
    printf("シェルソート試行回数:%d\n",count);
    printf("挿入ソート試行回数:%d\n",count2);
    
    return 0;
}

