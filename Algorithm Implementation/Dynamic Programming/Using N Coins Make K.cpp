/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

int N,Q,W;
int coin[Size];
bool DP[1005][1005];

bool coin_Change(int N,int W){
	for(int i = 0;i<=N;i++){
		for(int j = 0;j<=W;j++){
			DP[i][j] = false;
		}
	}
	for(int i = 0;i<N;i++){
		DP[i][coin[i]] = true;
	}
	for(int i = 1;i<=W;i++){
		for(int j = 1;j<N;j++){
			if(coin[j] <= i){
				if(DP[j-1][i-coin[j]] == true){
					DP[j][i] = true;
				}
			}
			if(DP[j-1][i] == true){
				DP[j][i] = true;
			}
		}
	}
	for(int i = 0;i<N;i++){
		if(DP[i][W] == true) return true;
	}
	return false;
}

int main() {
	scanf("%d %d",&N,&W);
	for(int i = 0;i<N;i++){
		scanf("%d",&coin[i]);
	}
}
