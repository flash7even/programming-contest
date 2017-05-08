/// Problem Link: http://www.spoj.com/problems/COT/
/// Editorial: https://blog.anudeep2011.com/persistent-segment-trees-explained-with-spoj-problems/
/// Idea: Persistent Segment Tree

#include <bits/stdc++.h>
using namespace std;

#define Size 100055
#define LN 18

int N, MX;
int Cost[Size];
vector<int> Graph[Size];
int sparseTable[Size][LN];
int depth[Size];

vector<int> List;
map<int, int> MAP;
int ORG[Size];

void compress(){
    sort(List.begin(), List.end());
    MAP[List[0]] = 1;
    ORG[1] = List[0];
    MX = 2;
    for(int i = 1;i<List.size();i++){
        if(List[i] != List[i-1]){
            MAP[List[i]] = MX;
            ORG[MX] = List[i];
            MX++;
        }
    }
}

struct node{
    int count;
    node * left;
    node * right;
	node(int count, node *left, node *right):
		count(count), left(left), right(right) {}

    node * ut(int s, int e, int u);
};

node * root[Size];
node * null = new node(0, NULL, NULL);

/// Remember: When you update a child v of u from original tree.
/// The root of v initially point to the root of u.
/// That means you are not copying the objects from u.
/// But you can access all the objects of u from this root.
/// When you call ut for v, at max log(N) nodes are created.
/// They get adjusted with the previous pointers copied from u.
/// No old objects are created, only the visiting pointers get updated
/// During the ut operation.

node * node::ut(int s,int e,int u){
    if(e < u || s > u) return this;
    if(s == e){
        return new node(this->count+1, null, null);
    }
    int M = (s+e)/2;

    node * ln = this->left->ut(s,M,u);
    node * rn = this->right->ut(M+1,e,u);

    return new node(this->count+1, ln, rn);
}

void DFS(int cur, int par, int level = 0) {

	if(par == -1) root[cur] = null;
	else root[cur] = root[par];

    root[cur] = root[cur]->ut(1, MX, MAP[Cost[cur]]);

	depth[cur] = level;
	int Sz = Graph[cur].size();

	for (int i = 0; i < Sz; i++) {
		int v = Graph[cur][i];
		if (v != par) {
			DFS(v, cur, level + 1);
			sparseTable[v][0] = cur;
		}
	}
}

void build_Sparse_Table() {
	sparseTable[1][0] = -1;
	for (int i = 1; i < LN; i++) {
		for (int j = 1; j <= N; j++) {
			sparseTable[j][i] = -1;
		}
	}
	for (int i = 1; i < LN; i++) {
		for (int j = 1; j <= N; j++) {
			if (sparseTable[j][i - 1] != -1) {
				sparseTable[j][i] = sparseTable[sparseTable[j][i - 1]][i - 1];
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

int qt(node * a, node * b, node * c, node * d, int s,int e,int k){
    if(s == e) return s;

    int M = (s+e)/2;

    int leftCnt = a->left->count + b->left->count - c->left->count - d->left->count;

    if(leftCnt >= k){
        return qt(a->left, b->left, c->left, d->left, s, M, k);
    }
    return qt(a->right, b->right, c->right, d->right, M+1, e, k - leftCnt);
}

void solve(int u, int v, int k){
    int lca = LCA(u, v);
    int par = sparseTable[lca][0];

    int res = qt(root[u], root[v], root[lca], (par == -1 ? null:root[par]), 1, MX, k);
    printf("%d\n", ORG[res]);
}

int main(){

    #ifdef forthright48
    freopen ( "input.txt", "r", stdin );
    /// freopen ( "output.txt", "w", stdout );
    #endif // forthright48

    int Q;
    scanf("%d %d",&N, &Q);
    for(int i = 1;i<=N;i++){
        scanf("%d",&Cost[i]);
        List.push_back(Cost[i]);
    }

    for(int i = 1;i<N;i++){
        int u,v;
        scanf("%d %d",&u, &v);
        Graph[u].push_back(v);
        Graph[v].push_back(u);
    }

    compress();
    null->left = null->right = null; /// Otherwise it'll cause RTE
    DFS(1, -1);
    build_Sparse_Table();

    for(int i = 1;i<=Q;i++){
        int u, v, k;
        scanf("%d %d %d",&u, &v, &k);
        solve(u, v, k);
    }

    return 0;
}
