struct Edge{
    int v,w;
};

int N,M;
vector<Edge> Graph[Size];
int dist[Size];

void ZeroOneBFS(int src){
    deque<Edge> dq;
    dq.push_front({src, 0});
    for(int i = 0;i<=N;i++) dist[i] = inf;
    dist[src] = 0;

    while(dq.size()>0){
        Edge cur = dq.front();
        dq.pop_front();

        for(int i = 0;i<Graph[cur.v].size();i++){
            Edge e = Graph[cur.v][i];
            int v = e.v, nw = cur.w + e.w;
            if(nw < dist[v]){
                if(e.w == 0) dq.push_front({v, nw});
                else dq.push_back({v, nw});
            }
        }
    }
}
