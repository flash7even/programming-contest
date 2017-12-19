/// 2 SAT Algorithm

const int NODE = 2e5; /// Maximum no of node (0 based indexing)

struct SCC{
    int nNode;
    int disc[NODE], low[NODE], col[NODE], cycle[NODE], st[NODE];
    vector<int> G[NODE];

    int sccIDX[NODE]; /// Only for two SAT code
    int sccCnt; /// Only for two SAT code

    /// cycle[u] = SCC leader of node u.
    /// Note: In any single SCC, one of them get selected as SCC leader.
    int tail, Time, cc;

    SCC():tail(0),Time(0),cc(0) {}
    void clear () {
        cc += 3;
        for(int i = 0;i<NODE;i++){
            G[i].clear();
            cycle[i] = i;
            sccIDX[i] = 0;
        }
        sccCnt = 0;
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
            sccCnt++;
            while ( 1 ) {
                int v = st[tail-1];
                tail--;
                col[v] = cc + 2;
                cycle[v] = u;
                sccIDX[v] = sccCnt;
                if ( u == v ) break;
            }
            sccIDX[u] = sccCnt;
        }
    }
    void findSCC( int N ) {
        for(int i = 0;i<=N;i++) {
            if ( col[i] <= cc ) {
                tarjan ( i );
            }
        }
    }
};


/// Change convert, depends on how input is provided.
/// Using clauses, populate SCC edges.
/// Call possible, to find if a valid solution is possible or not.
/// Call findSatNodes, to find true nodes.
/// Don't forget to keep space for !a variables.
/// SCC must be 0 based, because of the nature of convert.

struct SAT2 {
    SCC scc;
    vector<int> RES;

    void clear() {
        scc.clear();
        RES.clear();
    }

    int convert ( int n ) {
        int x = ABS(n);
        x--;
        x *= 2;
        if ( n < 0 ) x ^= 1;
        return x;
    }

    void mustTrue ( int a ) { /// A is True
        scc.G[a^1].pb ( a );
    }

    void xorClause ( int a, int b ) { /// A ^ B clause
        //!a->b !b->a a->!b b->!a
        scc.G[a^1].pb ( b );
        scc.G[a].pb( b^1 );
        scc.G[b^1].pb ( a );
        scc.G[b].pb ( a^1 );
    }

    void orClause ( int a, int b ) { /// A || B clause
        //!a->b !b->a
        scc.G[a^1].pb ( b );
        scc.G[b^1].pb ( a );
    }

    void andClause ( int a, int b ) { /// A ^ B clause
        mustTrue(a);
        mustTrue(b);
    }

    /// Out of all possible option, at most one is true
    void atMostOneClause ( int a[], int n, int flag ) {
        if ( flag == 0 ) { /// At most one can be false
            for(int i = 0;i<n;i++){
                a[i] = a[i] ^ 1;
            }
        }
        for(int i = 0;i<n;i++){
            for(int j = i+1;j<n;j++){
                orClause( a[i] ^ 1, a[j] ^ 1 ); /// !a || !b both being true not allowed
            }
        }
    }

    bool possible( int N ) {
        scc.findSCC( N );
        for(int i = 0;i<N;i++) {
            int a = i, b = i^1;
            /// a and !a can not be in the same SCC.
            if ( scc.cycle[a] == scc.cycle[b] ) return false;
        }
        /// Valid solution exists
        return true;
    }

    /// If !a is after a in the topological order, a should be FALSE.
    /// But it should be TRUE otherwise.
    /// Due to the property of SCC, it maintains a reverse
    /// topological order while assigning the sccIDX.
    /// So no need of extra topological sort to find the true values.
    void findSatNodes(int N){
        for(int u = 0;u<N;u+=2){
            if(scc.sccIDX[u] < scc.sccIDX[u^1]){
                RES.pb(u/2+1);
            }
        }
    }
}twoSat;
