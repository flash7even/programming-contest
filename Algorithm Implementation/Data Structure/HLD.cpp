/// Heavy Light Decomposition
/// Given a tree and a value for each node handle 2 operations
/// Update the value of a node
/// Answer sum of node between u and v

/**
    How To Use?
    Call clear() to clear all
    Define root
    Call DFS(root, -1) to process arrays
    Call HLD(root, -1) to build HLD
    Call bt(1, 1, Node) to build segment tree
    Call query(u, v) to answer query
    Call update(u, val) to update
    Note: everything is 1 based
**/

#define root 1
#define Size 100005
#define LN 20

int N, Node;
LL cost[Size];
vector<int> Graph[Size];
int treeAry[Size], subSize[Size], parent[Size];
int chainNo, chainInd[Size], chainHead[Size], posInTree[Size], depth[Size];
LL T[Size * 6]; /// For segment tree

void clear() {
    for (int i = 0; i <= N; i++) {
        treeAry[i] = 0;
        chainInd[i] = 0;
        chainHead[i] = -1;
        posInTree[i] = 0;
        subSize[i] = 0;
        cost[i] = 0;
    }
    CLR(T, 0);
    for (int i = 0; i <= N; i++) {
        Graph[i].clear();
    }
    chainNo = 0;
    Node = 1;
}

/// Section: Segment Tree (Modify according to problem)
void bt(int c, int s, int e) {
    if (s == e) {
        T[c] = treeAry[s];
        return;
    }
    int L = c*2,R = c*2+1,M = (s+e)/2;

    bt(L, s, M);
    bt(R, M + 1, e);
    T[c] = T[L] + T[R];
}

void ut(int c, int s, int e, int u, int v, LL value) {
    if(e < u || s > v) return;
    if (s >= u && e <= v) {
        T[c] = value;
        return;
    }
    int L = c*2,R = c*2+1,M = (s+e)/2;

    ut(L, s, M, u, v, value);
    ut(R, M + 1, e, u, v, value);
    T[c] = T[L] + T[R];
}

LL qt(int c, int s, int e, int u, int v) {
    if(e < u || s > v) return 0;
    if (s >= u && e <= v) {
        return T[c];
    }
    int L = c*2,R = c*2+1,M = (s+e)/2;

    LL v1 = qt(L, s, M, u, v);
    LL v2 = qt(R, M + 1, e, u, v);
    LL sum = v1 + v2;
    return sum;
}
/// endSection

/// Section: HLD
LL queryUp(int u, int v) {
    if (u == v) {
        return qt(1, 1, Node, posInTree[u], posInTree[u]);
    }
    int uchain, vchain = chainInd[v];
    LL ans = 0; /// Modify according to problem
    while (1) {
        uchain = chainInd[u];
        if (uchain == vchain) {
            int st = posInTree[v];
            int ed = posInTree[u];
            LL ret = qt(1, 1, Node, st, ed);
            ans += ret; /// Modify according to problem
            break;
        }
        int st = posInTree[chainHead[uchain]];
        int ed = posInTree[u];
        LL ret = qt(1, 1, Node, st, ed);
        ans += ret; /// Modify according to problem
        u = chainHead[uchain];
        u = parent[u];
    }
    return ans;
}

void HLD(int cur, int prev) {
    if (chainHead[chainNo] == -1) {
        chainHead[chainNo] = cur;
    }
    chainInd[cur] = chainNo;
    posInTree[cur] = Node;
    treeAry[Node++] = cost[cur];

    int mxChild = -1;
    for (int i = 0; i < (int) Graph[cur].size(); i++) {
        int v = Graph[cur][i];
        if (v != prev) {
            if (mxChild == -1 || subSize[mxChild] < subSize[v]) {
                mxChild = v;
            }
        }
    }

    if (mxChild != -1) {
        HLD(mxChild, cur);
    }

    for (int i = 0; i < (int) Graph[cur].size(); i++) {
        int v = Graph[cur][i];
        if (v != prev) {
            if (v != mxChild) {
                chainNo++;
                HLD(v, cur);
            }
        }
    }
}

void DFS(int cur, int prev, int level = 0) {
    subSize[cur] = 1;
    depth[cur] = level;
    parent[cur] = prev;
    for (int i = 0; i < (int) Graph[cur].size(); i++){
        int v = Graph[cur][i];
        if (v != prev) {
            DFS(v, cur, level + 1);
            subSize[cur] += subSize[v];
        }
    }
}

/// endSection

 /// Returns LCA of u and v
int LCA(int u, int v) {
    while (1) {
        int pu = chainHead[chainInd[u]], pv = chainHead[chainInd[v]];
        if (pu == pv) return depth[u]<depth[v] ? u : v;
        else {
            if (depth[pu] < depth[pv]) {
                v = parent[pv];
            }
            else {
                u = parent[pu];
            }
        }
    }
}

/// Returns the sum of the nodes between the path u to v
/// Modify according to problem
LL query(int u, int v) {
    int lca = LCA(u, v);
    LL ret1 = queryUp(u, lca);
    LL ret2 = queryUp(v, lca);
    LL merge = queryUp(lca, lca); /// Counted twice
    return (ret1 + ret2 - merge);
}

/// Update the value of u to val
void update(int u, LL val) {
    ut(1, 1, Node, posInTree[u], posInTree[u], val);
}

