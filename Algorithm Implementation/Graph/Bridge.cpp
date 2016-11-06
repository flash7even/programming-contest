/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;
#define Size 10005

int N, M;
int Time = 0;
vector<int> Graph[Size];
int disc[Size];
int low[Size];
int vis[Size];
int parent[Size];

struct Link{
    int s;
    int t;
    Link(int a,int b){
        s = a;
        t = b;
    }
};

vector<Link> bridge_List;

bool cmp(Link a,Link b){
    if(a.s == b.s) return (a.t<b.t);
    return (a.s<b.s);
}

void DFS(int cur) {
    disc[cur] = low[cur] = ++Time;
    vis[cur] = 1;

    for (int i = 0; i < (int) Graph[cur].size(); i++) {
        int v = Graph[cur][i];
        if (vis[v] == 0) {
            parent[v] = cur;
            DFS(v);
            low[cur] = min(low[v], low[cur]);
            if (low[v] > disc[cur]) {
                /// There is no way to reach cur from v without using this edge.
                /// So that's a bridge.
                bridge_List.pb(Link(cur,v));
            }
        } else if(v != parent[cur]) {
            low[cur] = min(disc[v], low[cur]);
        }
    }
}

void articulation_bridge() {
    mems(disc, 0);
    mems(low, 0);
    mems(vis, 0);
    mems(parent, -1);
    bridge_List.clear();

    for (int i = 0; i < N; i++) {
        if (vis[i] == 0) {
            DFS(i);
        }
    }
}

int main() {
    int u,v;
    sf("%d %d", &N, &M);
    for (int i = 0; i < N; i++){
        Graph[i].clear();
    }
    for (int i = 0; i < M; i++) {
        sf("%d %d", &u, &v );
        Graph[u].pb(v);
        Graph[v].pb(u);
    }
    articulation_bridge();
    sort(bridge_List.begin(),bridge_List.end(),cmp);
    pf("Total Bridges: %d\n",bridge_List.size());
    for(int i = 0;i<bridge_List.size();i++){
        pf("%d - %d\n",bridge_List[i].s,bridge_List[i].t);
    }
}
