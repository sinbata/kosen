#include<stdio.h>
int sum(int n){
	if(n==0)return 0;
	return n+sum(n-1);
}
int main (){
	int n;
	printf("���a:");
	scanf("%d",&n);
	printf("%d �̑��a:%d",n,sum(n));
	return 0;
}