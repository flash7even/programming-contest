#include <bits/stdc++.h>
using namespace std;

#define Size 100000100
long long ary[Size / 64 + 100];
unsigned pfList[5761558];

int cnt;

int sieve_with_bit_masking() {
	for (long long i = 3; i <= sqrt(Size); i += 2) {
		if (!(ary[i / 64] & (1LL << (i % 64)))) {
			for (long long j = i * i; j <= Size; j += 2 * i) {
				ary[j / 64] |= (1LL << (j % 64));
			}
		}
	}
	pfList[cnt++] = 2;
	for (long long i = 3; i <= Size; i += 2) {
		if (!(ary[i / 64] & (1LL << (i % 64)))) {
			pfList[cnt++] = i;
		}
	}
	return 0;
}

int main(){
	sieve_with_bit_masking();
	for(int i = 0;i<20;i++){
		printf("%d ",pfList[i]);
	}
}
