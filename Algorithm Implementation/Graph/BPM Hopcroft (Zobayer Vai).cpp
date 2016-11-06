/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

/**
    Hopcroft Bipartite Matching Complexity (sqrt(V)*E)
    Give a Chess board and some broken cells.Find how many
    knights can be placed there.
    Problem Link : http://lightoj.com/volume_showproblem.php?problem=1171
**/

#define INF 100000000
#define MAX 20001

int N, M, E, R, C;
/// N = Maximum number of matching possible from left set.

vector< int > Graph[MAX];
int Left[MAX];
int Right[MAX];
int dist[MAX];
int Mat[205][205];
int lCnt = 0,rCnt = 0;
/// lCnt = is max number of elements in left set.
/// rCnt = is max number of elements in right set.

bool BFS() {
	queue< int > Q;
	for(int i = 1; i<=N; i++) {
		if(Left[i] == 0) {
			dist[i] = 0;
			Q.push(i);
		} else {
            dist[i] = INF;
		}
	}
	dist[0] = INF;
	while(!Q.empty()) {
		int u = Q.front(); Q.pop();
		if(u != 0) {
			int len = Graph[u].size();
			for(int i = 0; i<len; i++) {
				int v = Graph[u][i];
				if(dist[Right[v]] == INF) {
					dist[Right[v]] = dist[u] + 1;
					Q.push(Right[v]);
				}
			}
		}
	}
	return (dist[0] != INF);
}

bool DFS(int u) {
	if(u != 0) {
		int len = Graph[u].size();
		for(int i = 0; i<len; i++) {
			int v = Graph[u][i];
			if(dist[Right[v]] == dist[u]+1) {
				if(DFS(Right[v])) {
					Right[v] = u;
					Left[u] = v;
					return true;
				}
			}
		}
		dist[u] = INF;
		return false;
	}
	return true;
}

int hopcroft_karp() {
	int matching = 0;
	mems(Left,0);
	mems(Right,0);
	N = lCnt;
	while(BFS()){
		for(int i = 1; i<=N; i++){
			if(Left[i] == 0 && DFS(i)){
				matching++;
			}
		}
	}
	return matching;
}

///   This part is only for building the graph    ///

bool isValid(int r, int c) {
	if(r<=0 || r>R || c<=0 || c>C) return false;
	return true;
}

void call(int r,int c,int d){
	if(d%2 == 1){
        Mat[r][c] = ++rCnt;
	} else {
		Mat[r][c] = ++lCnt;
		Graph[lCnt].clear();
	}
	for(int i = 0; i < 8; i++) {
		int r1 = r + knightDir[i][0];
		int c1 = c + knightDir[i][1];
		if(isValid(r1, c1) == true && Mat[r1][c1] != 0) {
			if(Mat[r1][c1] == -1){
                call(r1, c1, d + 1);
			}
			if(d%2 == 0) {
                int u = Mat[r][c];
                int v = Mat[r1][c1];
				Graph[u].push_back(v);
			}
		}
	}
}

void build_Graph(){
    for(int i = 1;i<=R;i++){
        for(int j = 1;j<=C;j++){
            if(Mat[i][j] == -1){
                call(i,j,0);
            }
        }
    }
}

///    Building of graph ends here for hopcroft graph.     ///

int main(){
    int u,v,nCase;
    sf("%d",&nCase);
    for(int cs = 1;cs<=nCase;cs++){
        sf("%d %d %d",&R,&C,&M);
        mems(Mat,-1);
        lCnt = rCnt = 0;
        for(int i = 0;i<M;i++){
            sf("%d %d",&u,&v);
            Mat[u][v] = 0;
        }
        build_Graph();
        N = lCnt;
        int ans = lCnt + rCnt - hopcroft_karp();
        printf("Case %d: %d\n",cs,ans);
    }
    return 0;
}
