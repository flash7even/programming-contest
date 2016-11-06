/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

#define MAX 305

vector<int>Graph[MAX] ;
int cost[MAX][MAX] ;
int par[MAX];
int source,sink;

void addEdge( int u , int v , int w ) {
    Graph[u].pb(v);
    Graph[v].pb(u);
    cost[u][v] = w;
}

int BFS( int source , int sink ) {
    mems(par , -1);
    queue< pair<int,int> > Q;
    Q.push( {source , inf } );
    while( !Q.empty() ) {
        pair<int,int> cur = Q.front() ;
        Q.pop();
        int u = cur.first ;
        int cap = cur.second ;
        for( int i = 0;i<Graph[u].size();i++) {
            int v = Graph[u][i] ;
            if(cost[u][v] > 0 && par[v] == -1) {
                par[v] = u ;
                cap = min( cost[u][v] , cap );
                if( v == sink ) return cap;
                Q.push( {v,cap} );
            }
        }
    }
    return 0;
}

void Ford_Fulkerson(){
    int flow = 0  ;
    while(flow = BFS( source , sink )) {
        for( int i = sink ; i != source ; i = par[i] ) {
            cost[par[i]][i] -= flow ;
            cost[i][par[i]] += flow ;
        }
    }
}

int main() {
    int nCase, N, M, w;
    sf("%d",&nCase );
    for(int cs = 1;cs<=nCase;cs++){
        sf("%d %d",&N,&M);
        for( int i = 0 ; i < MAX; i++ ){
            Graph[i].clear();
        }

        /// The main idea is to add edge from source to each diagonal
        /// and from each diagonal to sink (Capacity will be diagonal sum).
        /// Then to find the maximum flow the algorithm itself will
        /// adjust all the value between those diagonals to send
        /// maximum flow using their intersection edges.
        /// The value of each cell will be the remaining capacity between
        /// their intersection edges.

        mems(cost,0);
        source = 0;
        sink = 205;
        for( int i = 1 ; i < N+M; i++) {
            sf("%d",&w) ;
            addEdge(source , i , w );
        }
        for( int i = 1 ; i < N+M; i++) {
            sf("%d",&w);
            addEdge(i+100 , sink , w );
        }

        for( int i = 1 ; i <= N ; i++) {
            for( int j = 1 ; j <= M; j++ ) {
                int u = i+j-1;
                int v = i-j+M+100;
                addEdge(u,v,99);
                cost[source][u]--;
                cost[v][sink]--;
            }
        }

        Ford_Fulkerson();
        pf("Case %d:\n",cs);
        for( int i = 1 ; i <= N ; i++ ) {
            for( int j = 1 ; j <= M ; j++ ) {
                if( j != 1 ) pf(" ");
                int u = i-j+M+100;
                int v = i+j-1;
                int val = cost[u][v]+1;
                pf("%d",val);
            }
            pf("\n");
        }
    }
    return 0 ;
}
