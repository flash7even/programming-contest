const int NODE = 250500;    /// Maximum Nodes
const int LGN = 30;         /// Maximum Number of Tries
const int MXQ = 1000;       /// Maximum Patterns
const int MXCHR = 26;       /// Maximum Characters

struct node {
    int val;
    vector<int> endList;    /// List of patterns ends here
    int endCnt;             /// Number of times the prefix match with text
    int child[MXCHR];
    void clear(){
        CLR(child, 0);
        val = endCnt = 0;
        endList.clear();
    }
} Trie[NODE+10];

int maxNodeId, fail[NODE+10], par[NODE+10];
stack <int> nodeStack;       /// Free pool of nodes

void resetTrie() {
    maxNodeId = 0;
    while(!nodeStack.empty()) {
        nodeStack.pop();
    }
}

int getNode() {
    if (nodeStack.empty()) {
        maxNodeId++;
        nodeStack.push(maxNodeId);
    }
    int curNodeId = nodeStack.top();
    nodeStack.pop();
    Trie[curNodeId].clear();
    return curNodeId;
}

struct AhoCorasick {
    int root, size;
    int *qfound;
    vector <int> lvlNodes;      /// List of nodes sorted by level

    void clear() {
        root = getNode();
        size = 0;
    }

    AhoCorasick() {}

    AhoCorasick (int qf[]) {
        qfound = qf;
    }

    int getname(char ch){
        return (ch-'a');
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
        Trie[cur].endList.pb(id);
        size++;
    }

    void calcFailFunction(){
        queue <int> Q;
        Q.push(root);
        lvlNodes.clear();

        while(!Q.empty()){
            int s = Q.front();
            Q.pop();
            lvlNodes.pb(s);

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
        }
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

    void pushUp(){
        int len = SZ(lvlNodes);
        ROF(i,0,len-1){
            int u = lvlNodes[i];
            int f = fail[u];
            /// The prefix of my fall back node matches with my suffix
            /// So every time i match with text, my fall back node also match
            Trie[f].endCnt += Trie[u].endCnt;
            FOR(j,0,SZ(Trie[u].endList)-1){
                int qid = Trie[u].endList[j];
                qfound[qid] += Trie[u].endCnt;
            }
        }
    }

    /// Iterate through the whole text and find all the matchings
    void findmatching (string &s){
        int cur = root, idx = 0;
        int len = SZ(s);
        while(idx<len){
            int c = getname(s[idx]);
            cur = goTo(cur, c);
            Trie[cur].endCnt++;
            idx++;
        }
        pushUp();
    }

};

struct DynamicAhoCorasick {
    int curAC;
    int qfound[MXQ];            /// How many times i'th pattern matched
    AhoCorasick acorasick[LGN];

    void clear() {
        curAC = 0;
        CLR(qfound,0);
        resetTrie();
    }

    int merge(int u,int v){
        if (u == 0 || v == 0) {
            return u+v;
        }
        for(int i=0;i<MXCHR;i++) {
            Trie[u].child[i] = merge(Trie[u].child[i], Trie[v].child[i]);
        }
        for (int i=0; i<Trie[v].endList.size(); i++){
            int x = Trie[v].endList[i];
            Trie[u].endList.pb(x);
        }
        nodeStack.push(v);
        return u;  /// this is the new root after merging trees with root u and v
    }

    void insert(string &pattern, int id){
        acorasick[curAC] = AhoCorasick(qfound);
        acorasick[curAC].clear();
        acorasick[curAC].addToTrie(pattern,id);
        /// acorasick[curAC].calcFailFunction();
        curAC++;

        for(int i = curAC - 1; i >= 1; i--){
            int x = i-1, y = i;
            if(acorasick[x].size == acorasick[y].size){
                acorasick[x].root = merge(acorasick[x].root, acorasick[y].root);
                acorasick[x].size += acorasick[y].size;
                /// acorasick[x].calcFailFunction();
                curAC--;
            }
            else {
                break;
            }
        }
    }

    void findmatching(string &text){
        for(int i = 0; i < curAC; i++){
            acorasick[i].calcFailFunction();
            acorasick[i].findmatching(text);    /// run query for log(N) trees;
        }
        return;
    }


} dynAC;
