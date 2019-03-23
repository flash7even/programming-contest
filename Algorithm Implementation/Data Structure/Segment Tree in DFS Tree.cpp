/// Given a tree(rooted with 1) having N nodes and their initial weight
/// We have to handle two types of query
/// 1 u: Return sum of the weight of all nodes in subtree u
/// 2 u w: Change the weight of node u to w

#define root 1
#define Size 100055
#define LN 20

struct vert{
    int sum;
    int prop;
};

vector<int> Graph[Size];
int dis[Size], fin[Size], A[Size];

vert T[Size * 4];
int N, NNODE;

void bt(int c, int s, int e) {
	if (s == e) {
		T[c].sum = 1;
		return;
	}
	int L = c * 2, R = L + 1, M = (s + e) / 2;

	bt(L, s, M);
	bt(R, M + 1, e);
	T[c].sum = T[L].sum + T[R].sum;
}

void ut(int c, int s, int e, int u, int v, int val) {
	if (s > v || e < u) return;

	if (s >= u && e <= v) {
		T[c].sum = val;
		return;
	}
	int L = c * 2, R = L + 1, M = (s + e) / 2;

	ut(L, s, M, u, v, val);
	ut(R, M + 1, e, u, v, val);
	T[c].sum = T[L].sum + T[R].sum;
}

int qt(int c, int s, int e, int u, int v) {
	if (s > v || e < u) return 0;

	if (s >= u && e <= v) {
		return T[c].sum;
	}
	int L = c * 2, R = L + 1, M = (s + e) / 2;

	int v1 = qt(L, s, M, u, v);
	int v2 = qt(R, M + 1, e, u, v);
	return v1+v2;
}

void DFS(int c, int p) {
    NNODE++;
	dis[c] = NNODE;
	for (int i = 0; i < Graph[c].size(); i++){
		if (Graph[c][i] != p) {
			DFS(Graph[c][i], c);
		}
	}
	fin[c] = NNODE;
}
