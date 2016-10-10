#include <bits/stdc++.h>
using namespace std;

#define MAX 50000
#define LMT 216
#define RNG 100032

int mark[MAX/64];
int segment[RNG/64];
vector<int> pList;
int tPrime = 0;

#define chkC(x,n) (x[n>>6]&(1<<((n>>1)&31)))
#define setC(x,n) (x[n>>6]|=(1<<((n>>1)&31)))

void sieve() {
	for (int i = 3; i < LMT; i += 2) {
		if (!chkC(mark, i)) {
			for (int j = i * i; j < MAX; j += 2*i) {
				setC(mark, j);
			}
		}
	}
	for (int i = 3; i < MAX; i += 2) {
		if (!chkC(mark, i)){
			pList.pb(i);
		}
	}
	tPrime = pList.size();
}

int segmented_sieve(int a, int b) {
	int cnt = 0;
	if(a <= 2 && 2 <= b) cnt = 1;
	if (b < 2) return 0;
	if (a < 3) a = 3;
	if (a % 2 == 0) a++;
	mems(segment, 0);
	for (int i = 0;i<tPrime && pList[i]*pList[i] <= b; i++) {
		unsigned j = pList[i] * ((a + pList[i] - 1) / pList[i]);
		if (j % 2 == 0){
			j += pList[i];
		}
		for (int k = (pList[i] << 1); j <= b; j += k) {
			if (j != pList[i]) {
				setC(segment, (j - a));
			}
		}
	}
	for (int i = 0; i <= b - a; i += 2) {
		if (!chkC(segment, i)) {
			cnt++;
		}
	}
	return cnt;
}

int main() {
	sieve();
	int nCase,u,v;
	sf("%d",&nCase);
	for(int cs = 1;cs<=nCase;cs++){
		sf("%d %d",&u,&v);
		int res = segmented_sieve(u,v);
		pf("Case %d: %d\n",cs,res);
	}
    return 0;
}
