#include <bits/stdc++.h>
using namespace std;
#define Size 100005

/// This approach is memory efficient.
/// But depending on the problem statements we may need recursive approach.

struct node {
    int cnt;
    int child[55];
};

node tree[Size];

struct trie {
    void clear_new_node() {
        /// Whenever we create a new node we must initialize it.
        tree[node_ID].cnt = 0;
        memset(tree[node_ID].child, -1, sizeof tree[node_ID].child);
        node_ID++;
    }

    /// Counter for the number of distinct total nodes created.
    int node_ID;

    void initialize() {
        /// When initializing the root of our Trie.
        node_ID = 0;
        clear_new_node();
    }

    /// Returns the specific id for a character.
    /// Depends on the problem statement.
    int get_ID(const char &c){
      if(c >= 'A' && c <= 'Z') return c - 'A';
      else return (c - 'a') + 26;
    }

    /// Inserting a word in our Trie.
    /// cnt handles the number of finish points
    /// of the words inserted in the Trie.
    int insert_word(const string &s) {
        int cur_node = 0,Len = s.size();
        for (int i = 0; i < Len; ++i) {
            int id = get_ID(s[i]);
            if (tree[cur_node].child[id] == -1) {
                /// Make a new node if no node exist at this id.
                tree[cur_node].child[id] = node_ID;
                clear_new_node();
            }
            cur_node = tree[cur_node].child[id];
        }
        tree[cur_node].cnt++;
        return tree[cur_node].cnt;
    }

    /// Returns number of same word found in the Trie.
    int search_word(const string &s) {
        int cur_node = 0,Len = s.size();
        for (int i = 0; i < Len; ++i) {
            int id = get_ID(s[i]);
            if (tree[cur_node].child[id] == -1) {
                /// The word doesn't exist.
                return 0;
            }
            cur_node = tree[cur_node].child[id];
        }
        return tree[cur_node].cnt;
    }
};

trie root;

int N,M,len;

int main() {
    int nCase;
    string s,word;
    cin >> nCase;
    for (int cs = 1; cs <= nCase; cs++) {
        cin >> N;
        root.initialize();
        for (int i = 0; i < N; i++) {
            cin >> s;
            /// Insert the word in trie.
            root.insert_word(s);
        }
        cin >> M;
        for (int i = 0; i < M; i++) {
            cin >> word;
            int ret = root.search_word(word);
            /// Returns no of words same as word in the trie.
            printf("%d\n",ret);
        }
    }
    return 0;
}
