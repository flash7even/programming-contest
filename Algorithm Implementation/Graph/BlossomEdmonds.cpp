/**
    Maximum Matching in General Graph
    V->number of vertex, E->number of edges
    Call add_edge() to add edge (u -> v) (u -> v occur once)
    Call edmonds() to get maximum matching
    match[i] is matched pair of i (-1 if there isn't a matched pair)
    0 based vertex
**/

struct struct_edge{
    int v;
    struct_edge* n;
};

typedef struct_edge* edge;
struct_edge pool[Size*Size*2];
edge top = pool, adj[Size];

int V, E, qh,qt;
int match[Size], q[Size], father[Size], base[Size];
bool inq[Size], inb[Size];

void add_edge(int u,int v){
    top->v = v, top->n = adj[u], adj[u] = top++;
    top->v = u, top->n = adj[v], adj[v] = top++;
}

int LCA(int root,int u,int v){
    static bool inp[Size];
    CLR(inp, 0);
    while(1){
        inp[u = base[u]] = true;
        if (u == root) break;
        u = father[match[u]];
    }
    while(1){
        if (inp[v = base[v]]) return v;
        else v = father[match[v]];
    }
}

void mark_blossom(int lca,int u){
    while (base[u] != lca){
        int v = match[u];
        inb[base[u]] = inb[base[v]] = true;
        u = father[v];
        if(base[u] != lca) father[u] = v;
    }
}

void blossom_contraction(int s,int u,int v){
    int lca = LCA(s,u,v);
    CLR(inb,0);
    mark_blossom(lca,u);
    mark_blossom(lca,v);
    if (base[u] != lca) father[u] = v;
    if (base[v] != lca) father[v] = u;
    for (int u=0; u<V; u++)
        if (inb[base[u]]){
            base[u] = lca;
            if (!inq[u]) inq[q[++qt] = u] = true;
        }
}

int find_augmenting_path(int s){
    CLR(inq, 0);
    CLR(father, -1);
    for (int i=0; i<V; i++) base[i] = i;
    inq[q[qh = qt = 0] = s] = true;
    while (qh<=qt){
        int u = q[qh++];
        for (edge e = adj[u]; e; e = e->n){
            int v = e->v;
            if (base[u] != base[v] && match[u] != v){
                if ((v == s)||(match[v] != -1 && father[match[v]] != -1))
                    blossom_contraction(s,u,v);
                else if (father[v]==-1){
                    father[v] = u;
                    if (match[v] == -1) return v;
                    else if (!inq[match[v]]) inq[q[++qt] = match[v]] = true;
                }
            }
        }
    }
    return -1;
}

int augment_path(int s, int t){
    int u = t,v,w;
    while (u != -1){
        v = father[u];
        w = match[v];
        match[v] = u;
        match[u] = v;
        u = w;
    }
    return t != -1;
}

int edmonds(){
    int matchc = 0;
    CLR(match, -1);
    for (int u = 0; u<V; u++){
        if (match[u] == -1){
            matchc += augment_path(u,find_augmenting_path(u));
        }
    }
    for (int i = 0; i<V; i++){
        if (i<match[i]){
            /// i and match[i] is a matching
        }
    }
    return matchc;
}
