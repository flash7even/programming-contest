/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

#define MX 100005

int SATNODE;
int low[MX];
int disc[MX];
bool taken[MX];
vector<int> Graph[MX];
stack<int> st;
int scc[MX];

int Time = 0,sccID = 0;

void run_Tarjan_SCC(int u) {
    disc[u] = low[u] = ++Time;
    taken[u] = true;
    st.push(u);

    int Size = Graph[u].size();
    for (int i = 0; i < Size; i++) {
        int v = Graph[u][i];
        if (disc[v] == -1) {
            run_Tarjan_SCC(v);
            low[u] = min(low[u], low[v]);
        } else if (taken[v] == true) {
            low[u] = min(low[u], disc[v]);
        }
    }
    if (disc[u] == low[u]) {
        sccID++;
        while (st.top() != u) {
            int adj = st.top();
            taken[adj] = false;
            scc[adj] = sccID;
            st.pop();
        }
        int adj = st.top();
        taken[adj] = false;
        scc[adj] = sccID;
        st.pop();
    }
}

void find_SCC(int N) {
    for(int i = 0;i<N;i++){
        low[i] = disc[i] = -1;
        scc[i] = 0;
        taken[i] = false;
    }
    Time = -1;
    sccID = 0;
    for (int i = 0; i < N; i++) {
        if (disc[i] == -1) {
            run_Tarjan_SCC(i);
        }
    }
}

/// Change here,depends on how input is provided.
/// Convert the node to it's corresponding node in 2 sat.
int convertNode ( int n ) {
    int x = abs(n);
    x--;
    x *= 2;
    if ( n < 0 ) x ^= 1;
    return x;
}

/// a must be True
void addEdge_MustTrue ( int a ) {
    Graph[a^1].pb( a );
}

/// a || b clause ( a or b must be true)
void addEdge_OrClause ( int a, int b ) {
    /// !a->b , !b->a
    Graph[a^1].pb( b );
    Graph[b^1].pb( a );
}

vector<int> satRes;

/// Return false if it's impossible.
/// Otherwise return true and save the true nodes in satRes.
bool twoSAT(){
    find_SCC(SATNODE);
    for(int i = 0;i<SATNODE;i++){
        if(scc[i] == scc[i^1]) return false;
    }
    satRes.clear();
    for(int i = 0;i<SATNODE;i+=2){
        if(scc[i]<scc[i^1]){
            satRes.pb(i/2+1);
        }
    }
    return true;
}

int main(){
	int nCase,T,M,u,v;
	sf("%d",&nCase);
	for(int cs = 1;cs<=nCase;cs++){
        sf("%d %d",&T,&M);
        SATNODE = 2*M;
        for(int i = 0;i<SATNODE;i++){
            Graph[i].clear();
        }
        for(int i = 0;i<T;i++){
            sf("%d %d",&u,&v);
            u = convertNode(u);
            v = convertNode(v);
            addEdge_OrClause(u,v);
        }
        pf("Case %d: ",cs);
        if(twoSAT()){
            pf("Yes\n");
            pf("%d",satRes.size());
            for(int i = 0;i<satRes.size();i++){
                pf(" %d",satRes[i]);
            }
            pf("\n");
        }else{
            pf("No\n");
        }
	}
	return 0;
}
