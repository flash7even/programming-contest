#include <bits/stdc++.h>
using namespace std;
#define Size 100005

#define root 0
#define N 10100
#define LN 14

/// Problem Link : http://www.spoj.com/problems/QTREE/

vector<int> Graph[N], costs[N], edgeIdx[N];
int treeAry[N], Node;
int chainNo, chainInd[N], chainHead[N], posInTree[N];
int depth[N], sparseTable[N][LN], otherEnd[N], subSize[N];
int T[N * 6];
int n;

void bT(int cur, int st, int ed) {
	if (st == ed - 1) {
		T[cur] = treeAry[st];
		return;
	}
    int L = cur*2;
    int R = L+1;
    int M = (st+ed)/2;
	bT(L, st, M);
	bT(R, M, ed);
	T[cur] = max(T[L] , T[R]);
}

void uT(int cur, int st, int ed, int u, int val) {
	if (st > u || ed <= u) return;
	if (st == u && st == ed - 1) {
		T[cur] = val;
		return;
	}
    int L = cur*2;
    int R = L+1;
    int M = (st+ed)/2;
	uT(L, st, M, u, val);
	uT(R, M, ed, u, val);
	T[cur] = max(T[L] , T[R]);
}

int qT(int cur, int st, int ed, int u, int v) {
	if (st >= v || ed <= u) {
		return -1;
	}
	if (st >= u && ed <= v) {
		return T[cur];
	}
    int L = cur*2;
    int R = L+1;
    int M = (st+ed)/2;
	int v1 = qT(L, st, M, u, v);
	int v2 = qT(R, M, ed, u, v);
	return max(v1, v2);
}

int query_up(int u, int v) {
	if (u == v){
		return 0;
	}
	int uchain, vchain = chainInd[v], ans = -1;
	while (true) {
		uchain = chainInd[u];
		if (uchain == vchain) {
			if (u == v) break;
			int T = posInTree[v];
			int ed = posInTree[u];
			int ret = qT(1, 1, Node, T + 1,ed + 1);
			ans = max(ans, ret);
			break;
		}
		int T = posInTree[chainHead[uchain]];
		int ed = posInTree[u];
		int ret = qT(1, 1, Node, T, ed + 1);
		ans = max(ans, ret);
		u = chainHead[uchain];
		u = sparseTable[u][0];
	}
	return ans;
}

int LCA(int u, int v) {
	if (depth[u] < depth[v]){
		swap(u, v);
	}
	int diff = depth[u] - depth[v];
	for (int i = 0; i < LN; i++) {
		if ((diff >> i) & 1) {
			u = sparseTable[u][i];
		}
	}
	if (u == v) return u;
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
		for (int j = 0; j < N; j++) {
			if (sparseTable[j][i - 1] != -1) {
				sparseTable[j][i] = sparseTable[sparseTable[j][i - 1]][i - 1];
			}
		}
	}
}

void query(int u, int v) {
	int lca = LCA(u, v);
	int ret1 = query_up(u, lca);
	int ret2 = query_up(v, lca);
	ret1 = max(ret1,ret2);
	printf("%d\n", ret1);
}

void updateEdge(int i, int val) {
	int u = otherEnd[i];
	uT(1, 1, Node, posInTree[u], val);
}

void HLD(int curNode, int cost, int prev) {
	if (chainHead[chainNo] == -1) {
		chainHead[chainNo] = curNode;
	}
	chainInd[curNode] = chainNo;
	posInTree[curNode] = Node;
	treeAry[Node++] = cost;

	int newNode = -1, nCost;
	for (int i = 0; i < (int) Graph[curNode].size(); i++) {
		if (Graph[curNode][i] != prev) {
			if (newNode == -1 || subSize[newNode] < subSize[Graph[curNode][i]]) {
				newNode = Graph[curNode][i];
				nCost = costs[curNode][i];
			}
		}
	}

	if (newNode != -1) {
		HLD(newNode, nCost, curNode);
	}

	for (int i = 0; i < (int) Graph[curNode].size(); i++) {
		if (Graph[curNode][i] != prev) {
			if (newNode != Graph[curNode][i]) {
				chainNo++;
				HLD(Graph[curNode][i], costs[curNode][i], curNode);
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
			otherEnd[edgeIdx[cur][i]] = Graph[cur][i];
			DFS(Graph[cur][i], cur, level + 1);
			subSize[cur] += subSize[Graph[cur][i]];
		}
}

void initialize(){
	for (int i = 0; i < n; i++) {
		Graph[i].clear();
		costs[i].clear();
		edgeIdx[i].clear();
		chainHead[i] = -1;
		for (int j = 0; j < LN; j++) {
			sparseTable[i][j] = -1;
		}
	}
	chainNo = 0;
	Node = 1;
}

int main() {
	int nCase;
	scanf("%d ", &nCase);
	for (int cs = 1; cs <= nCase; cs++) {
		scanf("%d", &n);
		initialize();
		for (int i = 1; i < n; i++) {
			int u, v, c;
			scanf("%d %d %d", &u, &v, &c);
			u--;v--;
			Graph[u].push_back(v);
			costs[u].push_back(c);
			edgeIdx[u].push_back(i - 1);
			Graph[v].push_back(u);
			costs[v].push_back(c);
			edgeIdx[v].push_back(i - 1);
		}
		DFS(root, -1);
		HLD(root, -1, -1);
		bT(1, 1, Node);
		build_Sparse_Table();

		while (true) {
			char s[100];
			scanf("%s", s);
			if (s[0] == 'D') {
				break;
			}
			int a, b;
			scanf("%d %d", &a, &b);
			if (s[0] == 'Q') {
				query(a - 1, b - 1);
			} else {
				updateEdge(a - 1, b);
			}
		}
	}
}
