#include <bits/stdc++.h>
using namespace std;
#define pf printf
#define sf scanf
#define Max 100005

/// Complexity O(N*log(N)^2)

struct suffix {
	int nr[2];
	int idx;
};

int cmp(suffix a,suffix b) {
	if(a.nr[0] == b.nr[0]) return a.nr[1] < b.nr[1];
	else return (a.nr[0] < b.nr[0]);
}

char str[Max];
suffix T[Max];

int spTable[17][Max];
int suffix[Max];
/// suffix[i] = Actual index of the i'th suffix after sorting.

int ranks[Max];
int LCP[Max];
int N,step,cnt;

void build_Suffix_Array() {
	for (int i = 0; i < N; i++) {
		spTable[0][i] = (str[i] - 'a');
	}
	step = 1,cnt = 1;
	while (cnt < N) {
		for (int i = 0; i < N; i++) {
			T[i].nr[0] = spTable[step - 1][i];
			if(i+cnt < N) {
				T[i].nr[1] = spTable[step - 1][i + cnt];
			} else {
				T[i].nr[1] = -1;
			}
			T[i].idx = i;
		}
		sort(T, T + N, cmp);
		for (int i = 0; i < N; i++) {
			if(i > 0 && T[i].nr[0] == T[i - 1].nr[0]
					 && T[i].nr[1] == T[i - 1].nr[1]){
				spTable[step][T[i].idx] = spTable[step][T[i - 1].idx];
			} else {
				spTable[step][T[i].idx] = i;
			}
			suffix[spTable[step][T[i].idx]] = T[i].idx;
		}
		step++;
		cnt = cnt*2;
	}
	for(int i = 0;i<N;i++){
		ranks[suffix[i]] = i;
	}
}

/// LCP[i] = Longest common prefix of suffix[i] and suffix[i-1].

void build_LCP_Array() {
	LCP[0] = 0;
	for (int i = 1; i < N; i++) {
		LCP[i] = 0;
		int s1 = suffix[i];
		int s2 = suffix[i - 1];
		for (int k = step - 1; k >= 0; k--) {
			if (s1 >= N || s2 >= N) break;
			if (spTable[k][s1] == spTable[k][s2]) {
				s1 += (1 << k);
				s2 += (1 << k);
				LCP[i] += (1 << k);
			}
		}
	}
}

int main() {
	int nCase;
	sf("%d", &nCase);
	for (int cs = 1; cs <= nCase; cs++) {
		sf("%s", str);
		N = strlen(str);
		build_Suffix_Array();
		build_LCP_Array();
	}
}
