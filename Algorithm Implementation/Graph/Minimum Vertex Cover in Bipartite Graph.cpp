/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

#define INF 100000000
#define MAX 2005

vector<int>Graph[MAX];
int vis[MAX];
int Left[MAX],Right[MAX];
int taken[MAX];

bool DFS(int u) {
    if(vis[u]) return false;
    vis[u] = true;
    for(int i = 0;i<Graph[u].size();i++){
        int v = Graph[u][i];
        if(taken[u] || taken[v]) continue;
        if(Right[v] == -1){
            Right[v] = u, Left[u] = v;
            return true;
        }
    }
    for(int i = 0;i<Graph[u].size();i++){
        int v = Graph[u][i];
        if(taken[u] || taken[v]) continue;
        if(DFS(Right[v])){
            Right[v] = u, Left[u] = v;
            return true;
        }
    }
    return false;
}

/// Minimum vertex cover in bipartite graph,
/// find out minimum number of vertex needed to cover all the chain of edges.
/// For example (2-4-8-16) is considered a single chain(of edges).
/// And a single vertex is needed to cover a single chain(which may contain multiple edges).

int minVertexCover(int n) {
    int ret = 0;
    mems(Left,-1);
    mems(Right,-1);
    while(true) {
        bool done = true;
        mems(vis,0);
        for(int i = 1;i<=n;i++){
            if(taken[i]) continue;
            if(Left[i] == -1 && DFS(i)){
                done = false;
            }
        }
        if(done == true) break;
    }
    for(int i = 1;i<=n;i++){
        if(taken[i]) continue;
        ret += (Left[i] == -1);
    }
    return ret;
}

vector<int> A;
map<int,int> Map;

int main(){
    int nCase,M,N,u,v;
    sf("%d",&nCase);
    for(int cs = 1;cs<=nCase;cs++){
        sf("%d %d",&N,&M);
        for(int i = 0;i<=N+1;i++){
            Graph[i].clear();
        }
        for(int i = 0;i<M;i++){
            sf("%d %d",&u,&v);
            Graph[u].pb(v);
        }
        int mvc = minVertexCover(N);
        pf("Minimum Vertex Needed: %d\n",mvc);
    }
    return 0;
}
