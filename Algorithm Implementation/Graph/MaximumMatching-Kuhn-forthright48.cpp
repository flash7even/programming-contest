/*
1. Clear Graph
2. Add edges using adj
3. call match by passing highest index of nodes
4. remember, both sides have nodes from 1 to N.
   do not address right side nodes starting from N+1.
*/

#define NODE xxx

//Kuhn's Algo for finding Maximum matching
struct KUHN{
    int left[NODE], right[NODE], vis[2*NODE], cc; ///Node double in vis for vertex print
    vector<int> adj[NODE];

    KUHN() : cc(1) {}

    void clear( int n ) {
        FOR(i,0,n) adj[i].clear();
    }

    bool tryK ( int v ) {
        if ( vis[v] == cc ) return false;
        vis[v] = cc;
        for ( int i = 0; i < SZ(adj[v]); i++ ) {
            int t = adj[v][i];
            if ( right[t] == -1 ) {
                right[t] = v; left[v] = t;
                return true;
            }
        }
        for ( int i = 0; i < SZ(adj[v]); i++ ) {
            int t = adj[v][i];
            if ( tryK ( right[t] ) ) {
                right[t] = v; left[v] = t;
                return true;
            }
        }
        return false;
    }

    int match(int n) {
        int res = 0;
        bool done;
        CLR(left,-1); CLR(right,-1);
        do {
            done = true; cc++;
            FOR(i,0,n) {
                if(left[i]==-1 && tryK(i)) {
                    done = false;
                }
            }
        } while(!done);
        FOR(i,0,n) res += (left[i]!=-1);
        return res;
    }

    ///Careful. Loop runs from 0 to n-1
    ///Make sure match() has been run
    int lcover[NODE], rcover[NODE];
    void findVertexCover ( int n ) {
        queue<int> q;
        cc++;
        FOR(i,0,n-1){
            if ( left[i] == -1 ) {
                q.push ( i );
                vis[i] = cc;
            }
        };

        while ( !q.empty() ) {
            int s = q.front(); q.pop();
            FOR(i,0,SZ(adj[s])-1){
                int t = adj[s][i];
                if ( t == left[s] ) continue;

                int xt = t + n;
                if ( vis[xt] == cc ) continue;

                vis[xt] = cc;
                xt = right[t];

                if ( xt != -1 && vis[xt] != cc ) {
                    vis[xt] = cc;
                    q.push ( xt );
                }

            };
        }

        FOR(i,0,n-1){
            if ( vis[i] != cc ) lcover[i] = 1;
            else lcover[i] = 0;
        };
        FOR(i,0,n-1){
            if ( vis[i+n] == cc ) rcover[i] = 1;
            else rcover[i] = 0;
        };

    }
} kuhn;
