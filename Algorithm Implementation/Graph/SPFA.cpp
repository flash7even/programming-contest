/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;
const int MX = 250;

struct Edge{
    int v,cost;
    Edge(int a, int b){
        v = a;
        cost = b;
    }
};

vector<Edge> Graph[MX];
bool visited[MX];
int visitCnt[MX];
int dist[MX];
bool inCircle[MX];
int A[MX];

void DFS(int u){
    inCircle[u] = true;
    for(int i = 0; i < Graph[u].size(); i++){
        if(!inCircle[Graph[u][i].v]){
            DFS(Graph[u][i].v);
        }
    }
}

void SPFA(int start,int n){
    mems(visited,false);
    visited[start] = true;
    for(int i = 1; i <= n; i++){
        dist[i] = inf;
    }
    dist[start] = 0;
    queue<int> Q;
    Q.push(start);
    mems(visitCnt,0);
    visitCnt[start] = 1;
    mems(inCircle,false);

    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        visited[u] = false;
        int Sz = Graph[u].size();
        for(int i = 0; i < Sz; i++) {
            int v = Graph[u][i].v;
            if(inCircle[v]) continue;
            if(dist[v] > dist[u] + Graph[u][i].cost) {
                dist[v] = dist[u] + Graph[u][i].cost;
                if(!visited[v]) {
                    visited[v] = true;
                    Q.push(v);
                    visitCnt[v]++;
                    if(visitCnt[v] > n){
                        DFS(v);
                    }
                }
            }
        }
    }
}

int main(){
    int nCase,N,M,u,v;
    sf("%d",&nCase);
    for(int cs = 1;cs<=nCase;cs++){
        sf("%d",&N);
        for(int i = 1; i <= N; i++){
            sf("%d",&A[i]);
            Graph[i].clear();
        }
        sf("%d",&M);
        for(int i = 0;i<M;i++){
            sf("%d %d",&u,&v);
            int w = (A[v]-A[u])*(A[v]-A[u])*(A[v]-A[u]);
            Graph[u].pb(Edge(v,w));
        }
        SPFA(1,N);
        pf("Case %d:\n",cs);
        sf("%d",&M);
        for(int i = 0;i<M;i++){
            sf("%d",&u);
            if(inCircle[u] || dist[u] < 3 || dist[u] == inf){
                pf("?\n");
            } else {
                pf("%d\n",dist[u]);
            }
        }
    }
    return 0;
}
