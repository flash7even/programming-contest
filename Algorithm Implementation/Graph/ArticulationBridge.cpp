/// Articulation Bridge
/// Call findBridge() to find the articulation bridge

const int NODE = 2e5; /// Maximum no of node (1 based indexing)

vector<int> G[NODE];
int disc[NODE], low[NODE], vis[NODE], par[NODE];

struct Bridge{
    int Time = 0;

    Bridge():Time(0) {}
    void clear(){
        for(int u = 0;u<NODE;u++){
            G[u].clear();
            disc[u] = low[u]  = vis[u] = 0;
            par[u] = -1;
        }
    }
    void tarjan(int u) {
        disc[u] = low[u] = ++Time;
        vis[u] = 1;

        for (int i = 0; i < (int) G[u].size(); i++) {
            int v = G[u][i];
            if (vis[v] == 0) {
                par[v] = u;
                tarjan(v);
                low[u] = min(low[v], low[u]);
                if (low[v] > disc[u]) { /// u-v is a bridge
                    /// Do whatever you like now with it...
                }
            } else if(v != par[u]) {
                low[u] = min(disc[v], low[u]);
            }
        }
    }
    void findBridge(int N) {
        for (int i = 1; i <= N; i++) {
            if (vis[i] == 0) {
                tarjan(i);
            }
        }
    }
}bridge;
