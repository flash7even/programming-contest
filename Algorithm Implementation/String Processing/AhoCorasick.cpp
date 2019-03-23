const int NODE = 3000500;   /// Maximum Nodes
const int LGN = 30;         /// Maximum Number of Tries
const int MXCHR = 53;       /// Maximum Characters
const int MXP = 5005;       ///

struct node {
    int val;
    int child[MXCHR];
    vector <int> graph; 
    void clear(){
        CLR(child, 0);
        val =  0;
        graph.clear();
    }
} Trie[NODE+10];

int maxNodeId, fail[NODE+10], par[NODE+10];
int nodeSt[NODE+10], nodeEd[NODE+10];
vlong csum[NODE+10], pLoc[MXP];

void resetTrie() {
    maxNodeId = 0;
}

int getNode() {
    int curNodeId = ++maxNodeId;
    Trie[curNodeId].clear();
    return curNodeId;
}

inline void upd(vlong pos) {
    csum[pos]++;
    return;
}

inline vlong qry(vlong pos) {
    vlong res = csum[pos];
    return res;
}

struct AhoCorasick {
    int root, size, euler;

    void clear() {
        root = getNode();
        size = euler = 0;
    }

    inline int getname(char ch){
        if (ch == '-') return 52;
        else if (ch >= 'A' && ch <= 'Z') return 26+(ch-'A');
        else return (ch-'a');
    }

    void addToTrie(string &s, int id){
        /// Add string s to the Trie in general way
        int len = SZ(s);
        int cur = root;
        FOR(i,0,len-1){
            int c = getname(s[i]);
            if(Trie[cur].child[c] == 0){
                int curNodeId = getNode();
                Trie[curNodeId].val = c;
                Trie[cur].child[c] = curNodeId;
            }
            cur = Trie[cur].child[c];
        }
        ///
        pLoc[id] = cur;
        size++;
    }

    void calcFailFunction(){
        queue <int> Q;
        Q.push(root);

        while(!Q.empty()){
            int s = Q.front();
            Q.pop();

            /// Add all the children to the queue:
            FOR(i,0,MXCHR-1){
                int t = Trie[s].child[i];
                if(t != 0){
                    Q.push(t);
                    par[t] = s;
                }
            }

            if(s == root){      /// Handle special case when s is root
                fail[s] = root;
                par[s] = root;
                continue;
            }

            /// Find fall back of s:
            int p = par[s];
            int val = Trie[s].val;
            int f = fail[p];

            /// Fall back till you found a node who has got val as a child
            while(f != root && Trie[f].child[val] == 0){
                f = fail[f];
            }

            fail[s] = (Trie[f].child[val] == 0) ? root : Trie[f].child[val];

            /// Self fall back not allowed
            if(s == fail[s]) {
                fail[s] = root;
            }

            ///
            Trie[fail[s]].graph.push_back(s);
        }
    }

    void dfs(int pos) {
        ++euler;
        nodeSt[pos] = euler;
        for (auto x: Trie[pos].graph) {
            dfs(x);
        }
        nodeEd[pos] = euler;
    }

    /// Returns the next state
    int goTo(int state, int c){
        if(Trie[state].child[c] != 0){ /// No need to fall back
            return Trie[state].child[c];
        }

        /// Fall back now:
        int f = fail[state];
        while(f != root && Trie[f].child[c] == 0){
            f = fail[f];
        }
        int res = (Trie[f].child[c] == 0) ? root : Trie[f].child[c];
        return res;
    }

    /// Iterate through the whole text and find all the matchings
    void findmatching (string &s){
        int cur = root, idx = 0;
        int len = SZ(s);
        while(idx<len){
            int c = getname(s[idx]);
            cur = goTo(cur, c);
            upd(nodeSt[cur]);
            idx++;
        }
    }

} acorasick;