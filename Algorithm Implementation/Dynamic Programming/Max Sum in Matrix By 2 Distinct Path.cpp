/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

#define Size 1005
#define Max 100005
#define INF (1<<30)
#define Mod 1000000007

int A[105][105];
int DP[105][105][105];
int N,M;

int call(){
	mems(DP,0);
	DP[1][1][2] = A[1][1] + A[1][2];
	for(int c1 = 3;c1<=M;c1++){
		DP[1][1][c1] = DP[1][1][c1-1] + A[1][c1];
	}
	for(int r = 2;r<=N;r++){
		for(int c1 = 1;c1<=M;c1++){
			for(int c2 = c1+1;c2<=M;c2++){
				DP[r][c1][c2] = max(DP[r][c1][c2],
						DP[r-1][c1][c2] + A[r][c1] + A[r][c2]);
			}
		}
		for(int c1 = 2;c1<=M;c1++){
			for(int c2 = c1+1;c2<=M;c2++){
				DP[r][c1][c2] = max(DP[r][c1][c2],
						DP[r][c1-1][c2] + A[r][c1]);
			}
		}
		for(int c1 = 1;c1<=M;c1++){
			for(int c2 = c1+2;c2<=M;c2++){
				DP[r][c1][c2] = max(DP[r][c1][c2],
						DP[r][c1][c2-1] + A[r][c2]);
			}
		}
	}
	return DP[N][M-1][M];
}

int main(){
	int nCase;
	sf("%d",&nCase);
	for(int cs = 1;cs<=nCase;cs++){
		sf("%d %d",&N,&M);
		for(int i = 1;i<=N;i++){
			for(int j = 1;j<=M;j++){
				sf("%d",&A[i][j]);
			}
		}
		int res = call();
		pf("Case %d: %d\n",cs,res);
	}
}
