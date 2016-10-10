
#include <bits/stdc++.h>
using namespace std;
#define Size 100000005
#define MOD 1000000007

LL big_mod(LL N,LL P){
	if(P == 0) return 1;
	if(P%2 == 0){
		LL ret = big_mod(N,P/2);
		return ((ret%MOD)*(ret%MOD))%MOD;
	}else{
		return ((N%MOD)*(big_mod(N,P-1)%MOD))%MOD;
	}
}

//Repeated Squaring Method :
LL big_mod (LL b, LL p) {
    LL res = 1LL % MOD, x = b % MOD;
    while (p != 0) {
        if ( p & 1LL ) res = ( res * x ) % MOD;
        x = ( x * x ) % MOD;
        p >>= 1LL;
    }
    return res;
}

LL D,K,H;

int main() {
	int nCase;
	scanf("%d",&nCase);
	for(int cs = 1;cs<=nCase;cs++){
		scanf("%lld %lld %lld",&D,&K,&H);
		long long res = big_mod(D,K+1)/(D-1);
		printf("%lld\n",res);
	}
}
