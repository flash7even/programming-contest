/// Biconnected Components
/// Call findBCC() to find the bcc components

const int NODE = 2e5; /// Maximum no of node (1 based indexing)

int disc[NODE], low[NODE], vis[NODE];
vector <int> G[NODE];
stack< pii > st;

struct BCC{
    int Time = 0;

    BCC():Time(0) {}
    void clear(){
        for(int u = 0;u<NODE;u++){
            G[u].clear();
            disc[u] = low[u]  = vis[u] = 0;
        }
        while(!st.empty()) st.pop();
    }
    void tarjan(int u, int par) {
        vis[u] = 1;
        disc[u] = low[u] = ++Time;
        for(int i = 0; i < G[u].size(); i++) {
            int v = G[u][i];
            if(v == par) continue;
            if(!vis[v]) {
                st.push(MP(u, v));
                tarjan(v, u);
                if(low[v] >= disc[u]) { /// Found a new BCC x, modify here with your needs
                    pii tmp = MP(u, v), e;
                    do {
                        e = st.top(); /// e is an edge of BCC x
                        st.pop();
                    } while(e != tmp);
                }
                low[u] = min(low[u], low[v]);
            } else if(disc[v] < disc[u]) {
                st.push(MP(u, v));
                low[u] = min(low[u], disc[v]);
            }
        }
    }
    void findBCC(int N){
        for(int i = 1; i <= N; i++){
            if(disc[i] == 0){
                tarjan(i, -1);
            }
        }
    }
}bcc;
