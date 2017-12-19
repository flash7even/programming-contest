/// Find if a point is inside a non simple polygon
/// Build a graph connecting the line(as an edge between two vertex)
/// Call isInsidePolygon()
/// The idea was given by forthright48

vector<Point> List;
double DP[Size];
int vis[Size];
vector<int> Graph[Size];

/// Compute A dot B:
double dot(Point A, Point B){
    return (A.x * B.x + A.y * B.y);
}

///Compute AB dot AC
double dotBAC(Point A, Point B, Point C) {
    Point AB = {B.x - A.x, B.y - A.y}; /// AB vector
    Point AC = {C.x - A.x, C.y - A.y}; /// AC vector
    return dot(AB, AC);
}

/// Angel between vector (A-B) and (A-C)
double getAngel(Point A, Point B, Point C){
    double dotVal = dotBAC(A, B, C);
    double a = dotVal/(dist(A,B) * dist(A,C));
    if(a < -1.0) a = -1.0;
    if(a > 1.0) a = 1.0;
    return acos(a);
}

bool DFS(int cur, Point P){
    vis[cur] = 1;
    for(int i = 0;i<Graph[cur].size();i++){
        int v = Graph[cur][i];
        double a = DP[cur] + getAngel(P, List[v], List[cur]);
        if(vis[v] == -1){
            DP[v] = a;
            bool ret = DFS(v, P);
            if(ret == true) return true;
        }else{
            double dif = a - DP[v];
            if(dif+eps > 2.0*pi || dif < -2.0*pi+eps) return true;
        }
    }
    return false;
}

/// Add edge between adjacent vertices.
void addEdge(int u, int v){
    Graph[u].push_back(v);
    Graph[v].push_back(u);
}

bool isInsidePolygon(Point P){
    for(int i = 0;i<List.size();i++){
        addEdge(i,(i+1)%List.size());
        /// Change here, depends on polygon structure
    }
    CLR(vis,-1);
    for(int i = 0;i<List.size();i++){
        if(vis[i] == -1){
            DP[i] = 0.0;
            if(DFS(i, P)) return true;
        }
    }
    return false;
}
