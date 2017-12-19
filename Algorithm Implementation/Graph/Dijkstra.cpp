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

int dist[MAX];
int N, M;
vector<Edge> Graph[MAX];

void dijkstra(int s) {
	priority_queue<Edge> pQ = priority_queue<Edge>();
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
