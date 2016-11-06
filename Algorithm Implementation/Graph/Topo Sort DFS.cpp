/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

#define WHITE 0
#define GREY 1
#define BLACK 2

vector<int> Graph[100005];
vector<int> Ans;
int visited[100005];

bool DFS(int u) {
	visited[u] = GREY;
	bool no_cycle = true;
	int Size = Graph[u].size();
	for (int i = 0; i < Size; i++) {
		int v = Graph[u][i];
		if (visited[v] == WHITE) {
			no_cycle = DFS(v);
		} else if (visited[v] == GREY){
			return false;
		}
	}
	visited[u] = BLACK;
	Ans.push_back(u);
	return no_cycle;
}

bool Topological_Sort(int N) {
	Ans.clear();
	memset(visited, false, sizeof(visited));
	int no_cycle = true;
	for (int i = 0; i < N; i++) {
		if (visited[i] == WHITE){
			no_cycle &= DFS(i);
		}
	}
	return no_cycle;
}
