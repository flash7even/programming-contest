/// Call clear()
/// Build the graph the same way we do in KUHN
/// Call findMatching() to get maximum matching
/// If Left[u] != 0 then (u and Left[u]) make a matching
/// Complexity (sqrt(V)*E)

const int INF = 0x7fffffff;
const int NODE = 40005; /// Maximum no of node(1 based indexing)

int Left[NODE], Right[NODE], dist[NODE];
vector< int > G[NODE];

struct HOPCROFT{
    int nNode, matching;

    void clear(int N){
        matching = 0;
        CLR(Left, 0);
        CLR(Right, 0);
        nNode = N;
    }

    void addEdge(int u, int v){
        G[u].pb(v);
    }

    bool BFS() {
        queue< int > Q;
        for(int i = 1; i<=nNode; i++) {
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
                int len = G[u].size();
                for(int i = 0; i<len; i++) {
                    int v = G[u][i];
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
            int len = G[u].size();
            for(int i = 0; i<len; i++) {
                int v = G[u][i];
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

    int findMatching(int nNode) {
        while(BFS()){
            for(int i = 1; i<=nNode; i++){
                if(Left[i] == 0 && DFS(i)){
                    matching++;
                }
            }
        }
        return matching;
    }
}hopcroft;
