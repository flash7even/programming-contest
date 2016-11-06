/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

#define Size 100005
#define INF 20

#define Size 100005
#define INF 20

int Set(int N,int pos){
    return N = N | (1<<pos);
}

/// Problem Link : http://lightoj.com/volume_showproblem.php?problem=1406

int DP[(1 << 16)+5];
bool visited[16][(1 << 16)+5];

bool subset[(1 << 16)+5];
/// subset[m] = true if all nodes in m can be covered using one assassin.
vector<int> Graph[16];
int N, E;

void DFS(int cur, int mask) {
	visited[cur][mask] = true;
	subset[mask] = true;
	/// We can cover the nodes in this mask using one assassin.
	int Sz = Graph[cur].size();
	for (int i = 0; i < Sz; i++) {
		int adj = Graph[cur][i];
		int nMask = Set(mask,adj);
		if (visited[adj][nMask] == false) {
			DFS(adj, nMask);
		}
		/// else we have already faced same scenario before and updated the result.
	}
}

/// Initially all the nodes in mask are uncovered.
/// We'll try for all possible subset and check if that subset can be covered by 1 assassin,
/// Then we'll call for new mask excluding that subset.
/// We'll update the optimal one among all possible options.

int call(int mask) {
	if (mask == 0) {
		return 0;
	}
	if (DP[mask] != -1) {
		return DP[mask];
	}
	int ret = INF;
	for (int subMask = mask; subMask > 0; subMask = (mask & (subMask - 1))) {
        /// subMask is one of the subset of mask.
		if (subset[subMask] == true) {
			int rr = call(mask ^ subMask) + 1; /// excluding subMask from mask.
			ret = min(ret,rr);
		}
	}
	return DP[mask] = ret;
}

int main() {
	int nCase, u, v;
	sf("%d", &nCase);
	for (int cs = 1; cs <= nCase; cs++) {
		sf("%d %d", &N, &E);
		for (int j = 0; j < N; j++) {
			Graph[j].clear();
		}
		for (int j = 0; j < E; j++) {
			sf("%d %d", &u, &v);
			u--, v--;
			Graph[u].pb(v);
		}
		CLR(visited, false);
		CLR(subset, false);
		for (int j = 0; j < N; j++) {
			DFS(j, (1 << j));
		}
		CLR(DP, -1);
		int mask = (1 << N) - 1;
		/// Initially all bits are one which means all of them are uncovered.
		int res = call(mask);
		printf("Case %d: %d\n", cs, res);
	}
	return 0;
}
