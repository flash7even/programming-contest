/// Max Flow Dinitz (Zobayer)
/// clear()
/// Build graph
/// Call findFLOW() to find maximum flow

const int INF = 0x7fffffff;
const int MAXN = 1e5, MAXE = 2e5;
/// Maximum no of nodes and edges.

int Q[MAXN], fin[MAXN], pro[MAXN], dist[MAXN];
int flow[MAXE], cap[MAXE], nxt[MAXE], to[MAXE];

struct DINITZ{
    int src, snk, nNode, nEdge;

    /// Parameters: (source, sink, no of nodes)
    void clear(int _src, int _snk, int _n) {
        src = _src, snk = _snk;
        nNode = _n, nEdge = 0;
        CLR(fin, -1);
    }

    /// Parameters: (from, to, capacity)
    void addEdge(int u, int v, int _cap) {
        to[nEdge] = v, cap[nEdge] = _cap, flow[nEdge] = 0;
        nxt[nEdge] = fin[u], fin[u] = nEdge++;
        /// Make this 2nd capacity zero for directed edge
        to[nEdge] = u, cap[nEdge] = _cap, flow[nEdge] = 0;
        nxt[nEdge] = fin[v], fin[v] = nEdge++;
    }

    bool BFS() {
        int st, en;
        CLR(dist, -1);
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
                int cur_flow  = DFS(v, min(cap[e] - flow[e], fw));
                if (cur_flow  > 0) {
                    flow[e] += cur_flow;
                    flow[e ^ 1] -= cur_flow;
                    return cur_flow;
                }
            }
        }
        return 0;
    }

    LL findFLOW() {
        LL fflow = 0;
        while (BFS()) {
            for (int i = 0; i <= nNode; i++) {
                pro[i] = fin[i];
            }
            while (true) {
                LL fw = DFS(src, INF);
                if (fw > 0) {
                    fflow += fw;
                } else {
                    break;
                }
            }
        }
        return fflow;
    }

}dinitz;
