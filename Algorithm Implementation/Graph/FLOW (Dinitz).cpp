/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

const int INF = 0x7fffffff;
const int MAXN = 105, MAXE = 5005*4;

int src, snk, nNode, nEdge;
int Q[MAXN], fin[MAXN], pro[MAXN], dist[MAXN];
int flow[MAXE], cap[MAXE], nxt[MAXE], to[MAXE];

inline void init(int _src, int _snk, int _n) {
	src = _src, snk = _snk;
	nNode = _n, nEdge = 0;
	mems(fin, -1);
}

inline void add_Edge(int u, int v, int c) {
	to[nEdge] = v, cap[nEdge] = c, flow[nEdge] = 0;
	nxt[nEdge] = fin[u], fin[u] = nEdge++;
	to[nEdge] = u, cap[nEdge] = c, flow[nEdge] = 0;
	nxt[nEdge] = fin[v], fin[v] = nEdge++;
}

bool BFS() {
	int st, en;
	mems(dist, -1);
	dist[src] = st = en = 0;
	Q[en++] = src;
	while (st < en) {
		int u = Q[st++];
		for (int i = fin[u]; i >= 0; i = nxt[i]) {
			int v = to[i];
			if (flow[i] < cap[i] && dist[v] == -1) {
				dist[v] = dist[u] + 1;
				Q[en++] = v;
			}
		}
	}
	return dist[snk] != -1;
}

int DFS(int u, int fw) {
	if (u == snk) return fw;
	for (int &e = pro[u]; e >= 0; e = nxt[e]) {
		int v = to[e];
		if (flow[e] < cap[e] && dist[v] == dist[u] + 1) {
			int cur_flow = DFS(v, min(cap[e] - flow[e], fw));
			if (cur_flow > 0) {
				flow[e] += cur_flow;
				flow[e ^ 1] -= cur_flow;
				return cur_flow;
			}
		}
	}
	return 0;
}

LL dinitz() {
	LL total_flow = 0;
	while (BFS()) {
		for (int i = 1; i <= nNode; i++) {
			pro[i] = fin[i];
		}
		while (true) {
			LL cur_flow = DFS(src, INF);
			if (cur_flow > 0) {
				total_flow += cur_flow;
			} else {
				break;
			}
		}
	}
	return total_flow;
}

int main() {
	int n, e, u, v, c,s,t;
    /// n is number of node and e is edge.
	/// s is source and t is destination.
	/// 1 based index for node.
	int nCase;
	sf("%d",&nCase);
	for(int cs = 1;cs<=nCase;cs++){
        scanf("%d %d %d %d", &n, &s, &t, &e);
        init(s, t, n);
        for (int i = 0; i < e; i++) {
            scanf("%d %d %d", &u, &v, &c);
            if (u != v) {
                add_Edge(u, v, c);
            }
        }
        LL max_Flow = dinitz();
        printf("Case %d: %lld\n", cs, max_Flow);
	}
	return 0;
}
