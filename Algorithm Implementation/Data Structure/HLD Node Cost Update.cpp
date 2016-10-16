#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define Size 100005

#define root 1
#define MAX 100005
#define LN 20

/// Problem Link : http://lightoj.com/volume_showproblem.php?problem=1348
/// Aladdin and the return journey.

vector<int> Graph[MAX];
int treeArray[MAX], Node;
int chainNo, chainInd[MAX], chainHead[MAX], posInTree[MAX];
int depth[MAX], sparseTable[MAX][LN], subSize[MAX];
LL T[MAX * 6];
LL Cost[MAX];
int N;

void initialize() {
	for (int i = 0; i <= N; i++) {
		treeArray[i] = 0;
		chainInd[i] = 0;
		chainHead[i] = -1;
		posInTree[i] = 0;
		depth[i] = 0;
		subSize[i] = 0;
		Cost[i] = 0;
	}
	memset(sparseTable, -1, sizeof(sparseTable));
	memset(T, 0, sizeof(T));
	for (int i = 0; i <= N; i++) {
		Graph[i].clear();
	}
	chainNo = 0;
	Node = 1;
}

void bT(int cur, int st, int ed) {
	if (st == ed) {
		T[cur] = treeArray[st];
		return;
	}
	int L = cur * 2;
	int R = L + 1;
	int M = (st + ed) / 2;
	bT(L, st, M);
	bT(R, M + 1, ed);
	T[cur] = T[L] + T[R];
}

void uT(int cur, int st, int ed, int u, int v, LL value) {
	if (st > v || ed < u)
		return;
	if (st >= u && ed <= v) {
		T[cur] = value;
		return;
	}
	int L = cur * 2;
	int R = L + 1;
	int M = (st + ed) / 2;

	uT(L, st, M, u, v, value);
	uT(R, M + 1, ed, u, v, value);
	T[cur] = T[L] + T[R];
}

LL qT(int cur, int st, int ed, int u, int v) {
	if (st > v || ed < u) {
		return 0;
	}
	if (st >= u && ed <= v) {
		return T[cur];
	}
	int L = cur * 2;
	int R = L + 1;
	int M = (st + ed) / 2;

	LL v1 = qT(L, st, M, u, v);
	LL v2 = qT(R, M + 1, ed, u, v);
	LL sum = v1 + v2;
	return sum;
}

LL query_up(int u, int v) {
	if (u == v) {
		return qT(1, 1, Node, posInTree[u], posInTree[u]);
	}
	int uchain, vchain = chainInd[v];
	LL ans = 0;
	while (true) {
		uchain = chainInd[u];
		if (uchain == vchain) {
			int st = posInTree[v];
			int ed = posInTree[u];
			LL ret = qT(1, 1, Node, st, ed);
			ans += ret;
			break;
		}
		int st = posInTree[chainHead[uchain]];
		int ed = posInTree[u];
		LL ret = qT(1, 1, Node, st, ed);
		ans += ret;
		u = chainHead[uchain];
		u = sparseTable[u][0];
	}
	return ans;
}

int LCA(int u, int v) {
	if (depth[u] < depth[v]) {
		swap(u, v);
	}
	int diff = depth[u] - depth[v];
	for (int i = 0; i < LN; i++) {
		if ((diff >> i) & 1) {
			u = sparseTable[u][i];
		}
	}
	if (u == v) {
		return u;
	}
	for (int i = LN - 1; i >= 0; i--) {
		if (sparseTable[u][i] != sparseTable[v][i]) {
			u = sparseTable[u][i];
			v = sparseTable[v][i];
		}
	}
	return sparseTable[u][0];
}

void build_Sparse_Table() {
	for (int i = 1; i < LN; i++) {
		for (int j = 1; j <= N; j++) {
			if (sparseTable[j][i - 1] != -1) {
				sparseTable[j][i] = sparseTable[sparseTable[j][i - 1]][i - 1];
			}
		}
	}
}

LL query(int u, int v) {
	int lca = LCA(u, v);
	LL ret1 = query_up(u, lca);
	LL ret2 = query_up(v, lca);
	LL merge = query_up(lca, lca);
	return (ret1 + ret2 - merge);
}

void updateNode(int u, LL val) {
	uT(1, 1, Node, posInTree[u], posInTree[u], val);
}

void HLD(int curNode, int prev) {
	if (chainHead[chainNo] == -1) {
		chainHead[chainNo] = curNode;
	}
	chainInd[curNode] = chainNo;
	posInTree[curNode] = Node;
	treeArray[Node++] = Cost[curNode];

	int newNode = -1;
	for (int i = 0; i < (int) Graph[curNode].size(); i++) {
		if (Graph[curNode][i] != prev) {
			if (newNode == -1 || subSize[newNode] < subSize[Graph[curNode][i]]) {
				newNode = Graph[curNode][i];
			}
		}
	}

	if (newNode != -1) {
		HLD(newNode, curNode);
	}

	for (int i = 0; i < (int) Graph[curNode].size(); i++) {
		if (Graph[curNode][i] != prev) {
			if (newNode != Graph[curNode][i]) {
				chainNo++;
				HLD(Graph[curNode][i], curNode);
			}
		}
	}
}

void DFS(int cur, int prev, int level = 0) {
	sparseTable[cur][0] = prev;
	depth[cur] = level;
	subSize[cur] = 1;
	for (int i = 0; i < (int) Graph[cur].size(); i++)
		if (Graph[cur][i] != prev) {
			DFS(Graph[cur][i], cur, level + 1);
			subSize[cur] += subSize[Graph[cur][i]];
		}
}

int main() {
	int nCase, Q, typ, u, v;
	LL val;
	scanf("%d", &nCase);
	for (int cs = 1; cs <= nCase; cs++) {
		scanf("%d", &N);
		initialize();
		for (int i = 1; i <= N; i++) {
			scanf("%lld", &Cost[i]);
		}
		for (int i = 0; i < N - 1; i++) {
			scanf("%d %d", &u, &v);
			u++, v++;
			Graph[u].push_back(v);
			Graph[v].push_back(u);
		}
		DFS(root, -1);
		HLD(root, -1);
		bT(1, 1, Node);
		build_Sparse_Table();
		printf("Case %d:\n", cs);
		scanf("%d", &Q);

		for (int i = 0; i < Q; i++) {
			scanf("%d", &typ);
			if (typ == 0) {
				scanf("%d %d", &u, &v);
				u++, v++;
				LL ans = query(u, v);
				printf("%lld\n", ans);
			} else {
				scanf("%d %lld", &u, &val);
				u++;
				updateNode(u, val);
			}
		}
	}
	return 0;
}
