/// Persistent Segment Tree
/// Call clear()
/// Call findRoots() to pre calculate the roots for each of the prefix.
/// Note: For calling bt() and qt() segment tree range(s and e)
/// depends on for which purpose we are using it.
/// In this case, we are using array elements as index.
/// So our range is 1 to N (Max A[i] can be N)
/// Change this accordingly.

const int MAXN = 1e5*20+50;
int A[Size];

struct persistentTree{
    int ID;
    int tree[MAXN], child[MAXN][2], root[MAXN];
    /// root[u] is the root of segment tree for prefix 1 to u

    void clear(){
        ID = 1;
        CLR(tree, 0);
        child[1][0] = child[1][1] = -1;
    }

    /// Build the segment tree for each prefix
    int bt(int c, int s, int e, int u){
        if(e < u || s > u) return c;
        if(s == e){
            ++ID;
            tree[ID] = tree[c] + A[u];
            return ID;
        }
        int M = (s+e)/2;
        if(child[c][0] == -1) child[c][0] = ++ID;
        if(child[c][1] == -1) child[c][1] = ++ID;

        int lid = bt(child[c][0], s, M, u);
        int rid = bt(child[c][1], M+1, e, u);

        ID++;
        tree[ID] = tree[c] + A[u];
        child[ID][0] = lid;
        child[ID][1] = rid;
        return ID;
    }

    /// Find the summation of values from u to v in the range (c1+1) to c2
    int qt(int c1, int c2, int s, int e, int u, int v){
        if(e < u || s > v) return 0;
        if(s >= u && e <= v){
            return tree[c2] - tree[c1];
        }
        int M = (s+e)/2;

        int nc1 = 0, nc2 = 0;
        if(child[c1][0] != -1) nc1 = child[c1][0];
        if(child[c2][0] != -1) nc2 = child[c2][0];
        int r1 = qt(nc1, nc2, s, M, u, v);

        nc1 = nc2 = 0;
        if(child[c1][1] != -1) nc1 = child[c1][1];
        if(child[c2][1] != -1) nc2 = child[c2][1];
        int r2 = qt(nc1, nc2, M+1, e, u, v);

        return r1+r2;
    }

    /// N is total number of elements
    void findRoots(int N){
        root[0] = 1;
        for(int i = 1;i<=N;i++){
            root[i] = bt(root[i-1], 1, N, i);
        }
    }

}persistent;
