const int Size = 1000005; /// Maximum Text Length
const int NODE = 250005; /// Maximum Nodes
const int MXQ = 505; /// Maximum Patterns
const int MXL = 505; /// Maximum Length Of Pattern
const int MXCHR = 26; /// Maximum Characters

struct node{
    int val;
    vector<int> endList; /// List of patterns ends here
    int endCnt; /// Number of times the prefix match with text
    int child[MXCHR];
    void clear(){
        CLR(child, 0);
        val = endCnt = 0;
        endList.clear();
    }
}trie[NODE];

int qfound[MXQ]; /// How many times i'th pattern matched
vector<int> lvlNodes; /// List of nodes sorted by level

struct AhoCorasick{
    int curNodeId, root, fail[NODE], par[NODE];

    void clear(){
        trie[root].clear();
        root = curNodeId = 0;
        lvlNodes.clear();
        CLR(qfound,0);
    }

    int getname(char ch){
        return (ch-'a');
    }

    void addTrie(string s, int id){
        /// Add string s to the trie in general way
        int len = SZ(s);
        int cur = root;
        FOR(i,0,len-1){
            int c = getname(s[i]);
            if(trie[cur].child[c] == 0){
                curNodeId++;
                trie[curNodeId].clear();
                trie[curNodeId].val = c;
                trie[cur].child[c] = curNodeId;
            }
            cur = trie[cur].child[c];
        }
        trie[cur].endList.pb(id);
    }

    void calcFailFunction(){
        queue<int> Q;
        Q.push(root);
        while(!Q.empty()){
            int s = Q.front();
            Q.pop();
            lvlNodes.pb(s);
            /// Add all the child to the queue:
            FOR(i,0,MXCHR-1){
                int t = trie[s].child[i];
                if(t != 0){
                    Q.push(t);
                    par[t] = s;
                }
            }

            if(s == 0){ /// Handle special case when s is root
                fail[s] = 0;
                par[s] = 0;
                continue;
            }

            /// Find fall back of s:
            int p = par[s];
            int val = trie[s].val;
            int f = fail[p];
            /// Fall back till you found a node who has got val as a child
            while(f != 0 && trie[f].child[val] == 0){
                f = fail[f];
            }
            fail[s] = trie[f].child[val];
            if(s == fail[s]) fail[s] = 0; /// Self fall back not allowed
        }
    }

    /// Returns the next state
    int goTo(int state, int c){
        if(trie[state].child[c] != 0){ /// No need to fall back
            return trie[state].child[c];
        }

        /// Fall back now:
        int f = fail[state];
        while(f != 0 && trie[f].child[c] == 0){
            f = fail[f];
        }
        return trie[f].child[c];
    }

    void pushUp(){
        int len = SZ(lvlNodes);
        ROF(i,0,len-1){
            int u = lvlNodes[i];
            int f = fail[u];
            /// The prefix of my fall back node matches with my suffix
            /// So every time i match with text, my fall back node also match
            trie[f].endCnt += trie[u].endCnt;
            FOR(j,0,SZ(trie[u].endList)-1){
                int qid = trie[u].endList[j];
                qfound[qid] += trie[u].endCnt;
            }
        }
    }

    /// Iterate through the whole text and find all the matchings
    void findmatching(string s){
        int cur = root, idx = 0;
        int len = SZ(s);
        while(idx<len){
            int c = getname(s[idx]);
            int prv = cur;
            cur = goTo(cur, c);
            trie[cur].endCnt++;
            idx++;
        }
        pushUp();
    }
}acorasick;
