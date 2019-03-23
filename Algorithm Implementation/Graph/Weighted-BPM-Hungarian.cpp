/**
    1. Call clear
    2. Left side nodes: 1 to n, right side nodes: 1 to m
    3. Assign weight for an edge(u,v) in weight[u][v]
    4. Call findMatching for maximum/minimum matching
    5. Call printMatching for printing the matching
**/

#define MAXIMIZE +1
#define MINIMIZE -1
const int MAX = 1005;

struct matching{
    bool visited[MAX];
    int U[MAX], V[MAX], P[MAX], way[MAX], minv[MAX], match[MAX];
    int weight[MAX][MAX], ar[MAX][MAX];

    void clear(){
        CLR(weight, 0);
        CLR(U, 0); CLR(V, 0); CLR(P, 0);
        CLR(ar, 0); CLR(way, 0);
    }

    /// If flag = MAXIMIZE, it'll maximize cost.
    int findMatching(int n, int m, int flag){
        FOR(i,1,n){
            FOR(j,1,m){
                ar[i][j] = weight[i][j];
                if(flag == MAXIMIZE) ar[i][j] = -ar[i][j];
            }
        }

        if(n>m) m = n;
        int a, b, d, r, w;

        FOR(i,1,n){
            P[0] = i, b = 0;
            FOR(j,0,m){
                minv[j] = inf, visited[j] = false;
            }
            do{
                visited[b] = true;
                a = P[b], d = 0, w = inf;
                FOR(j,1,m){
                    if(!visited[j]){
                        r = ar[a][j] - U[a] - V[j];
                        if(r < minv[j]) minv[j] = r, way[j] = b;
                        if(minv[j] < w) w = minv[j], d = j;
                    }
                }
                FOR(j,0,m){
                    if(visited[j]) U[P[j]] += w, V[j] -= w;
                    else minv[j] -= w;
                }
                b = d;
            }while(P[b] != 0);

            do{
                d = way[b];
                P[b] = P[d], b = d;
            }while(b != 0);
        }
        FOR(j,1,m) match[P[j]] = j;
        return (flag == MINIMIZE)? -V[0] : V[0];
    }

    void printMatching(int n, int m){
        vector<pii> L;
        FOR(i,1,n){
            int j = match[i];
            if(weight[i][j]) L.pb(MP(i, j));
        }
        int sz = SZ(L);
        printf("%d\n", sz);
        FOR(i,0,sz-1){
            printf("%d %d\n",L[i].ff,L[i].ss);
        }
    }

}hungarian;
