/// Strongly Connected Component
/// Call findSCC() to find all the scc
/// Call shrink() to convert each SCC into a single node
/// Note: After shrink() if cycle[u] != u then just ignore the node
/// Because in the new graph you only consider the scc heads

const int NODE = 2e5; /// Maximum no of node (1 based indexing)

int disc[NODE], low[NODE], col[NODE], cycle[NODE], st[NODE];
vector<int> G[NODE];
/// cycle[u] = SCC leader of node u.
/// Note: In any single SCC, one of them get selected as SCC leader.

struct SCC{
    int tail, Time, cc;

    SCC():tail(0),Time(0),cc(0) {}
    void clear () {
        cc += 3;
        for(int i = 0;i<NODE;i++){
            G[i].clear();
            cycle[i] = i;
        }
        tail = 0;
    }
    void tarjan ( int u ) {
        disc[u] = low[u] = Time++;
        col[u] = cc + 1;
        st[tail++] = u;
        for(int i = 0;i<SZ(G[u]);i++) {
            int v = G[u][i];
            if ( col[v] <= cc ) {
                tarjan ( v );
                low[u] = min(low[u], low[v]);
            } else if (col[v] == cc+1){ /// Back edge
                low[u] = min(low[u], low[v]);
            }
        }
        if ( low[u] == disc[u] ) { /// Found a SCC where u is the SCC leader
            while ( 1 ) {
                int v = st[tail-1];
                tail--;
                col[v] = cc + 2;
                cycle[v] = u;
                if ( u == v ) break;
            }
        }
    }

    void shrink( int N ) {
        for(int i = 1;i<=N;i++) {
            for(int j = 0;j<SZ(G[i]);j++) {
                G[i][j] = cycle[G[i][j]];
                /// This will create self-loop.
                /// Just ignore i->i edges while processing.
            }
        }
        for(int i = 1;i<=N;i++) {
            if ( cycle[i] == i ) continue;
            int u = cycle[i];
            for(int j = 0;j<SZ(G[i]);j++) {
                int v = G[i][j];
                G[u].pb ( v );
            }
            G[i].clear();
        }
        for(int i = 1;i<=N;i++) { /// Not always necessary
            sort ( ALL(G[i]) );
            UNIQUE(G[i]);
        }
    }

    void findSCC( int N ) {
        for(int i = 1;i<=N;i++) {
            if ( col[i] <= cc ) {
                tarjan ( i );
            }
        }
    }
}scc;
