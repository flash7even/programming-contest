/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

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

int N,M;

int main() {
    int nCase, u, v;
    scanf("%d", &nCase);
    for (int cs = 1; cs <= nCase; cs++) {
        scanf("%d %d", &N, &M);
        /// Clear Graph.
        for (int i = 0; i < M; i++) {
            scanf("%d %d", &u, &v);
            Graph[u].pb(v);
        }
        find_SCC();
    }
}
