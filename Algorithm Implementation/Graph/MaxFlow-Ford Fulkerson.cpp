#define Size 1005

int V,E;
int rGraph[Size][Size];
int graph[Size][Size];
bool visited[Size];
int parent[Size];

bool find_Path(int s, int t) {
	mems(visited, 0);
	queue<int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int v = 0; v < V; v++) {
			if (visited[v] == false && rGraph[cur][v] > 0) {
				q.push(v);
				parent[v] = cur;
				visited[v] = true;
			}
		}
	}
	return (visited[t] == true);
}

int ford_Fulkerson(int s, int t) {
	for (int i = 0; i < V; i++){
		for (int j = 0; j < V; j++){
			rGraph[i][j] = graph[i][j];
		}
	}
	int max_flow = 0;
	while (find_Path(s, t)) {
		int path_flow = INT_MAX;
		for (int v = t; v != s; v = parent[v]) {
			int u = parent[v];
			path_flow = min(path_flow, rGraph[u][v]);
		}
		for (int v = t; v != s; v = parent[v]) {
			int u = parent[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
		}
		max_flow += path_flow;
	}
	return max_flow;
}
