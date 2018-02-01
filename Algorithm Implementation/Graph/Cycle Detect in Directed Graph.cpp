/// Find if a cycle exist in a directed graph
/// Detects own cycle too
/// Complexity: O(V+E)

vector<int> Graph[Size];

struct cycleDetect{

    bool visited[Size];
    bool inStack[Size];

    bool go(int u){
        if(visited[u] == false){
            visited[u] = true;
            inStack[u] = true;
            FOR(i,0,SZ(Graph[u])-1){
                int v = Graph[u][i];
                if (!visited[v] && go(v))
                    return true;
                else if (inStack[v])
                    return true;
            }

        }
        inStack[u] = false;
        return false;
    }

    bool findCycle(){
        for(int i = 1; i <= N; i++){
            visited[i] = false;
            inStack[i] = false;
        }
        for(int i = 1; i <= N; i++){
            if (go(i)){
                return true;
            }
        }
        return false;
    }
}cycle;
