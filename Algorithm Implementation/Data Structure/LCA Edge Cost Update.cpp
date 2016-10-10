#include <bits/stdc++.h>
using namespace std;
#define Size 50005

#define root 0
#define LN 17

/**
    We are given a tree where each edge has some weight associated with it.
    We need to answer some query like this:
    1) What is the total cost needed to reach node v from u.
    2) What is the maximum valued edge we'll use to reach v from u.
    We can handle both of them using sparse table.

    It can't any update operation.
    After some preprocessing it handles each query in log(N)
**/

int N, M, Q, u, v;
int sparseTable[Size][LN];

int rsTable[Size][LN];
/// For each node u it saves the total cost needed
/// to reach the 2^k 'th parent for all (1<=k<=LN).

int depth[Size];
vector<int> Graph[Size], costs[Size];

void DFS(int cur, int prev, int level = 0) {
	depth[cur] = level;
	int Sz = Graph[cur].size();
	for (int i = 0; i < Sz; i++) {
		int adj = Graph[cur][i];
		if (adj != prev) {
			DFS(adj, cur, level + 1);
			sparseTable[adj][0] = cur;
			rsTable[adj][0] = costs[cur][i];
		}
	}
}

void build_Sparse_Table() {
	DFS(root, -1);
	rsTable[0][0] = 0;
	sparseTable[0][0] = -1;
	for (int i = 1; i < LN; i++) {
		for (int j = 0; j < N; j++) {
			sparseTable[j][i] = -1;
			rsTable[j][i] = 0;
		}
	}
	for (int i = 1; i < LN; i++) {
		for (int j = 0; j < N; j++) {
			if (sparseTable[j][i - 1] != -1) {
				sparseTable[j][i] = sparseTable[sparseTable[j][i - 1]][i - 1];
				rsTable[j][i] = max(rsTable[j][i - 1], rsTable[sparseTable[j][i - 1]][i - 1]);
				/// For finding total edge cost:
				/// rsTable[j][i] = rsTable[j][i-1] + rsTable[sparseTable[j][i-1]][i-1];
			}
		}
	}
}

int LCA(int u, int v) {
	if (depth[u] < depth[v]) {
		swap(u, v);
	}
	int Mx = 0, lg = 1;
	while ((1 << lg) <= depth[u]) {
		lg++;
	}
	lg--;
	for (int i = lg; i >= 0; i--) {
		if (depth[u] - (1 << i) >= depth[v]) {
			Mx = max(Mx, rsTable[u][i]);
			u = sparseTable[u][i];
		}
	}
	if (u == v) {
		return Mx;
	}
	for (int i = LN - 1; i >= 0; i--) {
		if (sparseTable[u][i] != sparseTable[v][i]) {
			Mx = max(Mx, max(rsTable[u][i], rsTable[v][i]));
			u = sparseTable[u][i];
			v = sparseTable[v][i];
		}
	}
	Mx = max(Mx, max(rsTable[u][0], rsTable[v][0]));
	return Mx;
}

int main() {
	int nCase, Q;
	scanf("%d", &nCase);
	for (int cs = 1; cs <= nCase; cs++) {
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++) {
			Graph[i].clear();
			costs[i].clear();
		}
		int cost, u, v;
		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &u, &v, &cost);
			u--; v--;
			Graph[u].push_back(v);
			costs[u].push_back(cost);
			Graph[v].push_back(u);
			costs[v].push_back(cost);
		}
		build_Sparse_Table();
		printf("Case %d:\n", cs);
		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			scanf("%d %d", &u, &v);
			int ans = LCA(u - 1, v - 1);
			printf("%d\n", ans);
		}
	}
}
