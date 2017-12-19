/// Sparse Table
/// Call buildSparseTable() for preprocessing
/// Call LCA to find lca of node u and v
/// Call pathCost to find path length between u and v
/// Note: /// 1 based indexing

const int Size = 3e5;
const int LN = 23;

int root = 1;
vector<int> Graph[Size];
int spTable[Size][LN], rsTable[Size][LN], depth[Size];
/// spTable[u][k] = 2^k'th parent of u
/// rsTable[u][k] = distance between u and 2^k'th parent of u

struct sparseTable{

    void DFS(int cur, int p, int level = 0) {
        depth[cur] = level;
        int Sz = Graph[cur].size();
        for (int i = 0; i < Sz; i++) {
            int v = Graph[cur][i];
            if (v != p) {
                DFS(v, cur, level + 1);
                spTable[v][0] = cur;
                rsTable[v][0] = 1;
            }
        }
    }

    void buildSparseTable(int N) {
        DFS(root, -1);
        rsTable[root][0] = 0;
        spTable[root][0] = -1;
        for (int i = 1; i < LN; i++) {
            for (int j = 1; j <= N; j++) {
                spTable[j][i] = -1;
                rsTable[j][i] = 0;
            }
        }
        for (int i = 1; i < LN; i++) {
            for (int j = 1; j <= N; j++) {
                if (spTable[j][i - 1] != -1) {
                    spTable[j][i] = spTable[spTable[j][i - 1]][i - 1];
                    rsTable[j][i] = rsTable[j][i - 1] + rsTable[spTable[j][i - 1]][i - 1];
                }
            }
        }
    }

    /// Returns LCA of u and v
    int LCA(int u, int v) {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }
        int lg = 1;
        while ((1 << lg) <= depth[u]) {
            lg++;
        }
        lg--;
        for (int i = lg; i >= 0; i--) {
            if (depth[u] - (1 << i) >= depth[v]) {
                u = spTable[u][i];
            }
        }
        if (u == v) {
            return u;
        }
        for (int i = LN - 1; i >= 0; i--) {
            if (spTable[u][i] != spTable[v][i]) {
                u = spTable[u][i];
                v = spTable[v][i];
            }
        }
        return spTable[u][0];
    }

    /// Returns distance between u and v
    int pathCost(int u, int v) {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }
        int res = 0, lg = 1;
        while ((1 << lg) <= depth[u]) {
            lg++;
        }
        lg--;
        for (int i = lg; i >= 0; i--) {
            if (depth[u] - (1 << i) >= depth[v]) {
                res += rsTable[u][i];
                u = spTable[u][i];
            }
        }
        if (u == v) {
            return res;
        }
        for (int i = LN - 1; i >= 0; i--) {
            if (spTable[u][i] != spTable[v][i]) {
                res += rsTable[u][i];
                res += rsTable[v][i];
                u = spTable[u][i];
                v = spTable[v][i];
            }
        }
        res += rsTable[u][0];
        res += rsTable[v][0];
        return res;
    }

}sparse;
