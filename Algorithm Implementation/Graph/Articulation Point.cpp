/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

#define Size 10005

int N, M;
int Time = 0;
vector<int> Graph[Size];
int disc[Size];
int low[Size];
int ap[Size];
int visited[Size];
int parent[Size];

struct Link{
    int s;
    int t;
    Link(int u,int v){
        s = min(u,v);
        t = max(u,v);
    }
};

vector<Link> bridge_List;

bool cmp(Link a,Link b){
    if(a.s == b.s) return (a.t<b.t);
    return (a.s<b.s);
}

void find_AP(int cur) {
    disc[cur] = low[cur] = ++Time;
    visited[cur] = 1;
    int child = 0;

    for (int i = 0; i < (int) Graph[cur].size(); i++) {
        int v = Graph[cur][i];
        if (visited[v] == 0) {
            parent[v] = cur;
            child++;
            find_AP(v);
            if (parent[cur] == -1 && child > 1) {
                ap[cur] = 1;
            }
            low[cur] = min(low[v], low[cur]);
            if (parent[cur] != -1 && low[v] >= disc[cur]) {
                ap[cur] = 1;
            }
        } else if (v != parent[cur]) {
            low[cur] = min(disc[v], low[cur]);
        }
    }
}

int articulation_point() {
    mems(disc, 0);
    mems(low, 0);
    mems(ap, 0);
    mems(visited, 0);
    mems(parent, -1);
    bridge_List.clear();

    for (int i = 0; i < N; i++) {
        if (visited[i] == 0) {
            find_AP(i);
        }
    }
    int cnt = 0;
    for(int i = 1;i<=N;i++){
        if(ap[i] == 1) cnt++;
    }
    return cnt;
}

int main() {
    int nCase,u,v;
    sf("%d",&nCase);
    for(int cs = 1;cs<=nCase;cs++){
        sf("%d %d", &N, &M);
        for (int i = 1; i <= N; i++){
            Graph[i].clear();
        }
        for (int i = 0; i < M; i++) {
            sf("%d %d", &u, &v );
            Graph[u].pb(v);
            Graph[v].pb(u);
        }
        int cnt = articulation_point();
        pf("Case %d: %d\n",cs,cnt);
        for(int i = 1;i<=N;i++){
            if(ap[i] == 1) pf("AP: %d\n",i);
        }
    }
}
