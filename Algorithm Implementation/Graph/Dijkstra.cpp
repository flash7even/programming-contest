/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;
#define Size 1005

struct Edge {
	int v, w;
	Edge(int vv, int c) {
		v = vv;
		w = c;
	}
	bool operator <(const Edge& other) const {
		return w > other.w;
	}
};

priority_queue<Edge> pQ;
int dist[MAX];
int N, M;
vector<Edge> Graph[MAX];

void dijkstra(int s, int * dist) {
	pQ = priority_queue<Edge>();
	dist[s] = 0;
	pQ.push(Edge(s, 0));
	while (!pQ.empty()) {
		Edge cur = pQ.top();
		pQ.pop();
		int Sz = Graph[cur.v].size();
		for (int i = 0; i < Sz; i++) {
			Edge e = Graph[cur.v][i];
			if (cur.w + e.w < dist[e.v]) {
				dist[e.v] = cur.w + e.w;
				pQ.push(Edge(e.v, dist[e.v]));
			}
		}
	}
}

int main() {
	int nCase;
	scanf("%d", &nCase);
	for (int cs = 1; cs <= nCase; cs++) {
		scanf("%d %d", &N, &M);
		int u, v, w;
		for (int i = 1; i <= N; i++) {
			dist[i] = INF;
			Graph[i].clear();
		}
		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &u, &v, &w);
			Graph[u].push_back(Edge(v, w));
			Graph[v].push_back(Edge(u, w));
		}
		dijkstra(1, dist);

		int res = dist[N];
		if (res == INF) {
			printf("Case %d: Impossible\n", cs);
		} else {
			printf("Case %d: %d\n", cs, res);
		}
	}
	return 0;
}
