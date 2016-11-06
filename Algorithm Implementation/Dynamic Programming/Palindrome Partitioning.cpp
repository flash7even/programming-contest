/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

/// Minimum no of partition we can make such that each partition is palindrome.

int Len;
char s[1005];

int isPal[1005][1005];
int minCut[1005];

int palindrome_partitioning(){
	mems(isPal,0);
	for(int i = 0;i<Len;i++){
		isPal[i][i] = 1;
		minCut[i] = Max;
	}
	/// First calculate for each pair of index
	/// If that substring is a palindrome.
	for(int L = 2;L<=Len;L++){
		for(int i = 0;i<Len;i++){
			int j = i+L-1;
			if(j>=Len) break;
			if(L == 2){
				if(s[i] == s[j]){
					isPal[i][j] = 1;
				}
			}else{
				if(s[i] == s[j] && isPal[i+1][j-1] == 1){
					isPal[i][j] = 1;
				}
			}
		}
	}
	/// Now calculate minimum cut needed to
	/// make all the substring palindrome.
	minCut[0] = 1;
	for(int i = 1;i<Len;i++){
		if(isPal[0][i] == 1){
			minCut[i] = 1;
		}else{
			for(int j = 0;j<i;j++){
				if(isPal[j+1][i] == 1){
					minCut[i] = min(minCut[i],minCut[j]+1);
				}
			}
		}
	}
	return minCut[Len-1];
}

int main(){
	int nCase;
	sf("%d",&nCase);
	for(int cs = 1;cs<=nCase;cs++){
		sf("%s",s);
		Len = strlen(s);
		int res = palindrome_partitioning();
		pf("Case %d: %d\n",cs,res);
	}
}
