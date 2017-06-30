#include<stdio.h>
void sin(int n ){
	if(n<=0) return;
	int m;
	m=n%2;
	sin(n/2);
	printf("%d",m);
	return;
}
int main(){
	int n;
	printf("10i”:");
	scanf("%d",&n);
	sin(n);
	return 0;
}