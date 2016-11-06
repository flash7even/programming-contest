/**
    Find No of lattice points inside a triangle.
    and also on a line.
 **/

/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

LL X1,X2,X3,Y1,Y2,Y3;

LL GCD(LL a,LL b){
	if(b == 0) return a;
	return GCD(b,a%b);
}

LL Area(){
	return abs(X1*(Y2-Y3) + X2*(Y3-Y1) + X3*(Y1-Y2));
}

LL latticePointsOnLine(LL X1, LL Y1, LL X2, LL Y2){
	return GCD(abs(X1 - X2), abs(Y1 - Y2));
}

LL latticePointsOnTriangle(){
	LL b = GCD(abs(X1 - X2), abs(Y1 - Y2))
	       + GCD(abs(X2 - X3), abs(Y2 - Y3))
	       + GCD(abs(X3 - X1), abs(Y3 - Y1));
	return b;
}

LL runPicksTheorem(){
	/// cnt = no of lattice points inside triangle.
	LL cnt = (Area() - latticePointsOnTriangle() + 2)/2;
	return cnt;
}

int main() {
	int nCase;
	scanf("%d",&nCase);
	for(int cs = 1;cs<=nCase;cs++){
		scanf("%lld %lld %lld %lld %lld %lld",&X1,&Y1,&X2,&Y2,&X3,&Y3);
		long long res = runPicksTheorem();
		printf("%lld\n",res);
	}
}
