/**
    How To Use?
    1. Properly define the values of the const variables
    2. Call clear()
    3. Add each pattern by calling addTrie()
    4. Call failureFunction() to find failure of each node
    5. Call findmatching() to find the matching of each patterns
    6. qfound[i] = Number of times i'th pattern matched
**/

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
vector<int> lvlNodes[NODE]; /// List of nodes at i'th level

struct AhoCorasick{
    int curNodeId, root, fail[NODE], par[NODE];

    void clear(){
        root = curNodeId = 0;
        trie[root].clear();
        CLR(qfound, 0);
    }

    int getname(char ch){
        if(ch>='a' && ch<='z') return (ch-'a');
        return (ch-'A') + 26;
    }

    /// Parameters(pattern, pattern id)
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

    void failureFunction(){
        queue<int> Q;
        Q.push(root);
        while(!Q.empty()){
            int s = Q.front();
            Q.pop();
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
            /// Fall back till you find a node who has got val as a child
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

    /// DFS who add all the nodes to their level
    void pushUpDFS(int u, int lvl){
        lvlNodes[lvl].pb(u);
        FOR(i,0,MXCHR-1){
            int v = trie[u].child[i];
            if(v != 0){
                pushUpDFS(v, lvl+1);
            }
        }
    }

    /// Push up all the count from lowest to the highest levels
    void pushUp(){
        FOR(i,0,NODE-1){
            lvlNodes[i].clear();
        }
        pushUpDFS(0, 0);
        for(int lvl = MXL-1;lvl>=0;lvl--){
            FOR(i,0,SZ(lvlNodes[lvl])-1){
                int u = lvlNodes[lvl][i];
                int f = fail[u];
                /// The prefix of my fall back node matches with my suffix
                /// So every time I match with text, my fall back node also match
                trie[f].endCnt += trie[u].endCnt;
                FOR(j,0,SZ(trie[u].endList)-1){
                    int qid = trie[u].endList[j];
                    qfound[qid] += trie[u].endCnt;
                }
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
