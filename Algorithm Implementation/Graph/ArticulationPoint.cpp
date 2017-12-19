/// Articulation Point
/// Call findAP() to find the articulation points

const int NODE = 2e5; /// Maximum no of node (1 based indexing)

int disc[NODE], low[NODE], isap[NODE], vis[NODE], par[NODE];
vector<int> G[NODE];
/// isap[u] = 1 if u is an articulation point.

struct AP{
    int Time = 0;

    AP():Time(0) {}
    void clear(){
        for(int u = 0;u<NODE;u++){
            G[u].clear();
            disc[u] = low[u] = isap[u] = vis[u] = 0;
            par[u] = -1;
        }
    }
    void tarjan(int u) {
        disc[u] = low[u] = ++Time;
        vis[u] = 1;
        int ch = 0; /// No of unvisited child
        for (int i = 0; i < G[u].size(); i++) {
            int v = G[u][i];
            if (vis[v] == 0) {
                par[v] = u;
                ch++;
                tarjan(v);
                low[u] = min(low[v], low[u]);
                if (par[u] == -1 && ch > 1) isap[u] = 1; /// Found an AP
                if (par[u] != -1 && low[v] >= disc[u]) { /// Found an AP
                    isap[u] = 1;
                }
            } else if (v != par[u]) {
                low[u] = min(disc[v], low[u]);
            }
        }
    }
    void findAP(int N) {
        for (int i = 1; i <= N; i++) {
            if (vis[i] == 0) {
                tarjan(i);
            }
        }
    }
}ap;
