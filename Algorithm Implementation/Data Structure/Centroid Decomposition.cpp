#include <bits/stdc++.h>
using namespace std;

#define CLR(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define Size 100005

int N;
vector<int> Graph[Size];
int treeSize[Size];
char color[Size];
int vis[Size];

void DFS(int cur,int par){
    int Sz = Graph[cur].size();
    treeSize[cur] = 1;
    for(int i = 0;i<Sz;i++){
        int v = Graph[cur][i];
        if(v == par) continue;
        if(vis[v] == 1) continue;
        DFS(v,cur);
        treeSize[cur] += treeSize[v];
    }
}

int centroid(int cur,int par,int target){
    int Sz = Graph[cur].size();
    for(int i = 0;i<Sz;i++){
        int v = Graph[cur][i];
        if(v == par) continue;
        if(vis[v] == 1) continue;
        if(2*treeSize[v]>target){
            return centroid(v,cur,target);
        }
    }
    return cur;
}

int getCenter(int cur){
    DFS(cur,0);
    return centroid(cur,0,treeSize[cur]);
}

void decompose(int cur,char ch){
    int cc = getCenter(cur);
    vis[cc] = 1;
    color[cc] = ch;
    int Sz = Graph[cc].size();
    for(int i = 0;i<Sz;i++){
        int v = Graph[cc][i];
        if(vis[v] == 1) continue;
        decompose(v,ch+1);
    }
}

int main () {
    int u,v;
    scanf("%d",&N);
    for(int i = 0;i<N-1;i++){
        scanf("%d %d",&u,&v);
        Graph[u].pb(v);
        Graph[v].pb(u);
    }
    CLR(vis,0);
    decompose(1,'A');
    for(int i = 1;i<=N;i++){
        if(i != 1) printf(" ");
        printf("%c",color[i]);
    }
    printf("\n");
    return 0;
}
