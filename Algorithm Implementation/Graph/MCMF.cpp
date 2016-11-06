/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

const int INF = 999999999;
const int MAXN = 150,MAXE = 15000;

int src, snk, nNode, nEdge;
int fin[MAXN], pro[MAXN], dist[MAXN];
int cap[MAXE], cost[MAXE], nxt[MAXE], to[MAXE], from[MAXE];

inline void init(int _src, int _snk, int nodes) {
	nNode = nodes, nEdge = 0;
	src = _src, snk = _snk;
	CLR(fin, -1);
}

inline void addEdge(int u, int v, int _cap, int _cost) {
	from[nEdge] = u, to[nEdge] = v, cap[nEdge] = _cap;
	cost[nEdge] = _cost, nxt[nEdge] = fin[u], fin[u] = nEdge++;
	from[nEdge] = v, to[nEdge] = u, cap[nEdge] = 0;
	cost[nEdge] = -_cost, nxt[nEdge] = fin[v], fin[v] = nEdge++;
}

bool bellmanford() {
	bool flag = true;
	for(int i = 0;i<nNode;i++) {
		dist[i] = INF;
		pro[i] = -1;
	}
	dist[src] = 0;
	for (int it = 1; it < nNode && flag; it++) {
		flag = false;
		for (int u = 0; u < nNode; u++) {
			for (int i = fin[u]; i >= 0; i = nxt[i]) {
				int v = to[i];
				if (cap[i] && dist[v] > dist[u] + cost[i]) {
					dist[v] = dist[u] + cost[i];
					pro[v] = i;
					flag = true;
				}
			}
		}
	}
	return (dist[snk] < INF);
}

int mcmf(int &fcost) {
	int netflow, bot;
	netflow = fcost = 0;
	while (bellmanford()) {
		bot = INF;
		for (int u = pro[snk]; u >= 0; u = pro[from[u]]) {
			bot = min(bot, cap[u]);
		}
		for (int u = pro[snk]; u >= 0; u = pro[from[u]]) {
			cap[u] -= bot;
			cap[u ^ 1] += bot;
			fcost += bot * cost[u];
		}
		netflow += bot;
	}
	return netflow;
}

int main() {
	int nCase, fcost, n, u, v, cap, cst, e, P;
	scanf("%d", &nCase);
	for (int cs = 1; cs <= nCase; cs++) {
		scanf("%d %d %d", &n, &e, &P);
		/// P is the total flow we want to pass.
		/// Source is 1 and Sink is N.
		init(1, n+1, n+2);
		for (int i = 1; i <= e; i++) {
			sf("%d %d %d %d",&u,&v,&cap,&cst);
			addEdge(u, v, cap, cst);
			addEdge(v, u, 0, -cst);
			addEdge(v, u, cap, cst);
			addEdge(u, v, 0, -cst);
		}
		addEdge(n, n+1, P, 0);
		int mflow = mcmf(fcost);
		if(mflow == P){
            printf("Case %d: %d\n", cs, fcost);
		}else{
            printf("Case %d: impossible\n", cs);
		}
	}
	return 0;
}
