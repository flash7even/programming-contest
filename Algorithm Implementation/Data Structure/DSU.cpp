/// 1. Call setSize() to set the subtree size of each node
/// 2. Call DFS() to find result for each node
/// RES[] contains the answer

int N;
vector<int> G[Size];
int subsize[Size];
int heavy[Size];
LL cnt[Size];
LL RES[Size]; /// Answer for node u
int C[Size]; /// Color of node u

void setSize(int u, int p){
    FOR(i,0,SZ(G[u])-1){
        int v = G[u][i];
        if(v == p) continue;
        setSize(v, u);
        subsize[u] += subsize[v];
    }
    subsize[u]++;
}

void rem(int u, int p){
    cnt[C[u]]--;
    FOR(i,0,SZ(G[u])-1){
        int v = G[u][i];
        if(v == p || heavy[v]) continue;
        rem(v, u);
    }
}

/// After we call add, if we are currently at node u
/// in our DFS, then cnt[x] = number of color
/// in the subtree of u.
void add(int u, int p){
    cnt[C[u]]++;
    FOR(i,0,SZ(G[u])-1){
        int v = G[u][i];
        if(v == p || heavy[v]) continue;
        add(v, u);
    }
}

void findResult(int u){
    /// Calculate result
}

/// Whenever we return to a node u, only the info of
/// its heavy child should be stored in our array.
void DFS(int u, int p, int isheavy){
    int mxsize = 0, heavyChild = -1;

    /// Find the heavy child first
    FOR(i,0,SZ(G[u])-1){
        int v = G[u][i];
        if(v == p) continue;
        if(subsize[v]>mxsize){
            mxsize = subsize[v];
            heavyChild = v;
        }
    }

    FOR(i,0,SZ(G[u])-1){
        int v = G[u][i];
        if(v == p) continue;
        if(v == heavyChild) continue;
        DFS(v, u, 0); /// Only call the light edges
    }

    if(heavyChild != -1){
        DFS(heavyChild, u, 1); /// Call the heavy child now
        heavy[heavyChild] = 1;
    }

    add(u, p); /// Add current subtree excluding heavy child

    findResult(u); /// Find the result for u'th subtree

    if(heavyChild != -1){
        heavy[heavyChild] = 0;
    }

    /// When we'll return to the parent of u, u'th information
    /// will be necessary only if u is a heavy child of p
    if(isheavy == 0){
        rem(u, p);
    }
}
