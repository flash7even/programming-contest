/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

/**
    Given a matrix of '*' and 'o' and infinite no of 2*1 size scale.
    Minimum no of scale we need to cover all the *.
**/

#define Size 100005
#define Max 505

int N, M;
vector<int> Graph[Max];
int Left[Max];
int Right[Max];
int flag[Max];

bool matching_possible(int u) {
	int total = Graph[u].size();
	for (int i = 0; i < total; i++) {
		int adj = Graph[u][i];
		if (flag[adj] == 1)
			continue;
		flag[adj] = 1;
		if (Right[adj] == -1 || matching_possible(Right[adj])) {
			Left[u] = adj, Right[adj] = u;
			return true;
		}
	}
	return false;
}

int get_bpm(int total_vertex) {
	mems(Left, -1);
	mems(Right, -1);
	int cnt = 0;
	for (int i = 0; i < total_vertex; i++) {
		mems(flag, 0);
		if (matching_possible(i) == true) {
			cnt++;
		}
	}
	return cnt;
}

char s[Max][Max];
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};

int isValid(int x, int y){
    if (x >= 0 && x < N && y >= 0 && y < M) return 1;
    return 0 ;
}

int solve() {
    /// Initialize:
    int total_gold = 0;
	for (int i = 0; i < Max; i++) {
		Graph[i].clear();
	}

	/// First Build The Graph:
    for (int i = 0;i < N;i++){
        for (int j = 0;j < M;j++){
            if (s[i][j] == '*'){
                total_gold++;
                for (int k = 0;k < 4;k++){
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if (isValid(x, y) && s[x][y] == '*'){
                        int u = i*M + j;
                        int v = x*M + y;
                        Graph[u].pb(v);
                    }
                }
            }
        }
    }

    /// Run Kuhn:
    int match = get_bpm(N*M+5);
    return (total_gold - match/2);
}

int main() {
    int nCase;
    sf("%d",&nCase);
	for(int cs = 1;cs<=nCase;cs++) {
		sf("%d %d",&N,&M);
		for(int i = 0;i<N;i++){
            sf("%s",s[i]);
		}
		int res = solve();
		printf("Case %d: %d\n",cs,res);
	}
	return 0;
}
