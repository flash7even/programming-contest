#include <bits/stdc++.h>
using namespace std;
#define Size 100005
#define INF 20

int Set(int N,int pos){
    return N = N | (1<<pos);
}

int DP[(1 << 16)+5];
bool visited[16][(1 << 16)+5];
bool subset[(1 << 16)+5];
vector<int> Graph[16];
int N, E;

void DFS(int cur, int mask) {
	visited[cur][mask] = true;
	subset[mask] = true;
	int Sz = Graph[cur].size();
	for (int i = 0; i < Sz; i++) {
		int adj = Graph[cur][i];
		int nMask = Set(mask,adj);
		if (visited[adj][nMask] == false) {
			DFS(adj, nMask);
		}
	}
}

int call(int mask) {
	if (mask == 0) {
		return 0;
	}
	if (DP[mask] != -1) {
		return DP[mask];
	}
	int ret = INF;
	for (int i = mask; i > 0; i = (mask & (i - 1))) {
		if (subset[i] == true) {
			int rr = call(mask ^ i) + 1;
			ret = min(ret,rr);
		}
	}
	return DP[mask] = ret;
}

int main() {
	int nCase, u, v;
	scanf("%d", &nCase);
	for (int cs = 1; cs <= nCase; cs++) {
		scanf("%d %d", &N, &E);
		for (int j = 0; j < N; j++) {
			Graph[j].clear();
		}
		for (int j = 0; j < E; j++) {
			scanf("%d %d", &u, &v);
			u--, v--;
			Graph[u].push_back(v);
		}
		memset(visited, false, sizeof(visited));
		memset(subset, false, sizeof(subset));
		for (int j = 0; j < N; j++) {
			DFS(j, (1 << j));
		}
		memset(DP, -1, sizeof(DP));
		int mask = (1 << N) - 1;
		int res = call(mask);
		printf("Case %d: %d\n", cs, res);
	}
	return 0;
}
