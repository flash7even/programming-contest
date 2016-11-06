/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;
#define Size 1005
#define MAXN 100002

int DP[MAXN][5];
int parent[MAXN];
vector<int> Graph[MAXN];

void initialize() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < 3; j++) {
			DP[i][j] = -1;
		}
	}
}

int call(int u, int isGuard) {
	if (Graph[u].size() == 0) return 0;
	if (DP[u][isGuard] != -1) return DP[u][isGuard];
	int sum = 0;
	for (int i = 0; i < (int) Graph[u].size(); i++) {
		int v = Graph[u][i];
		if (v != parent[u]) {
			parent[v] = u;
			if (isGuard == 0){
				sum += call(v, 1);
			}else{
				sum += min(call(v, 1), call(v, 0));
			}
		}
	}
	return DP[u][isGuard] = sum + isGuard;
}

int main() {
	initialize();
	int n;
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		Graph[u].push_back(v);
		Graph[v].push_back(u);
	}
	int ans = 0;
	ans = min(call(1, 1), call(1, 0));
	printf("Ans is : %d\n", ans);
	return 0;
}
