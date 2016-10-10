#include <bits/stdc++.h>
using namespace std;

int extended_euclid(int A,int B,int * X,int * Y){
	int a = A,b = B,x = 0,y = 1,u = 1,v = 0;
	while(a!=0){
		int qtnt = b/a;
		int rem = b%a;
		int m = x - u*qtnt;
		int n = y - v*qtnt;
		b = a;a = rem;
		x = u,y = v;
		u = m;v = n;
	}
	*X = x,*Y = y;
	return b;
}

int main() {
	int A,B,X,Y;
	scanf("%d %d",&A,&B);
	int gcd = extended_euclid(A,B,&X,&Y);
	printf("X: %d , Y: %d and gcd: %d\n",X,Y,gcd);

}
