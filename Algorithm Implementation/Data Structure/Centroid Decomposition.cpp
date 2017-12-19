/// Centroid Decomposition
/// Find number of pair (u, v) whose distance is a prime
/// Call decompose(0, 0)
/// Note: 0 based vertex

const int NODE = 50005;
const int LOGN = 20;

LL N, ans, szz, primeSize = 0;
vector<int> Graph[NODE];
int black[NODE];
int ndist[LOGN][NODE],sz[NODE];
int prime[NODE];

struct centroidDecomposition{

    void clear(){
        ans = szz = 0;
        for(int i = 0;i<=N;i++){
            Graph[i].clear();
            black[i] = 0;
            sz[i] = 0;
        }
        CLR(ndist, 0);
    }

    /// Return the size of the tree
    void getSize(int u, int p){
        sz[u] = 1;
        szz++;
        for(int i = 0;i<Graph[u].size();i++){
            int v = Graph[u][i];
            if(black[v] == 1) continue;
            if(v != p){
                getSize(v, u),sz[u] += sz[v];
            }
        }
    }

    /// Return the center of the tree
    int getCenter(int u, int p) {
        for(int i = 0;i<Graph[u].size();i++){
            int v = Graph[u][i];
            if(black[v] == 1) continue;
            if(v != p && sz[v]>szz/2){
                return getCenter(v, u);
            }
        }
        return u;
    }

    /// Update the ndist array for this subtree
    /// For each x calculate how many path of length(from centroid) x exist there
    void updateSubtree(int u, int p, int level, int dist, int add){
        ndist[level][dist] += add;
        for(int i = 0;i<Graph[u].size();i++){
            int v = Graph[u][i];
            if(black[v] == 1) continue;
            if(v != p){
                updateSubtree(v, u, level, dist+1, add);
            }
        }
    }

    /// Update result for this subtree
    LL findRes(int u, int p, int level, int dist){
        LL ret = 0;

        /// Section:
        /// Change this part according to problem statement
        for(int i = 0;i<primeSize;i++){ /// Loop for all the primes
            if(prime[i] - dist<0) continue;
            if(ndist[level][prime[i] - dist] == 0) break;

            if(prime[i] != dist){ /// Not root
                ret += ndist[level][prime[i]-dist];
                /// We don't need to multiply by 2
                /// Because eventually this path will be counted twice
            }else{
                ret += 2*ndist[level][prime[i]-dist];
                /// Path from current node to the root
                /// Multiply by 2 so that this path is counted twice
            }
        }
        /// endSection

        for(int i = 0;i<Graph[u].size();i++){
            int v = Graph[u][i];
            if(black[v] == 1) continue;
            if(v != p){
                ret += findRes(v, u, level, dist+1);
            }
        }
        return ret;
    }

    void decompose(int root, int level){
        /// tree decomposing at root
        szz = 0;
        getSize(root,root);
        int ctr = getCenter(root, root);

        updateSubtree(ctr, ctr, level, 0, 1); /// Initially add all the subtree of root
        black[ctr] = 1;

        LL add = 0;
        int u = ctr;

        for(int i = 0;i<Graph[u].size();i++){
            int v = Graph[u][i];
            if(black[v] == 1) continue;
            updateSubtree(v, u, level, 1, -1); /// Remove current subtree
            add += findRes(v, u, level, 1);
            updateSubtree(v, u, level, 1, 1); /// Add current subtree again
        }

        ans += add/2; /// Each pair was counted twice

        for(int i = 0;i<Graph[u].size();i++){
            int v = Graph[u][i];
            if(black[v] == 1) continue;
            decompose(v, level+1);
        }

        for(int i = 0;i<NODE && ndist[level][i];i++){
            ndist[level][i] = 0;
        }
    }

}centroid;
