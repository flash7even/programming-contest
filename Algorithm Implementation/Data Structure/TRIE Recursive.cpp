#include <bits/stdc++.h>
using namespace std;
#define Size 150005

/// Recursive approach of trie.

class Trie {
	bool found;
	Trie *child[10];

	/// If found is true, a word finished here.

public:
	Trie() {
		found = false;
		for (int i = 0; i < 10; i++)
			child[i] = NULL;
	}

    /// Delete to save memory.
	void delete_trie() {
		for (int i = 0; i < 10; i++)
			if (child[i] != NULL) {
				child[i]->delete_trie();
				delete child[i];
			}
	}

	void insert_word(string &word, int pos) {
		if (pos == (int)word.length()){
			found = true;
		}
		int c = (int)(word[pos] - '0');
		if (child[c] == NULL) {
			child[c] = new Trie();
		}
		return child[c]->insert_word(word, ++pos);
	}

	bool search_word(string &word, int pos) {
		if (found == false){
			return false;
		}
		if (pos == (int)word.length()){
			return true;
		}
		int c = (int)(word[pos] - '0');
		if (child[c] == NULL) {
			return false;
		}
		return child[c]->search_word(word, ++pos);
	}
}*root;

int N,Q;
string s;

int main() {
    int nCase;
    cin >> nCase;
    for (int cs = 1; cs <= nCase; cs++) {
        cin >> N;
        root = new Trie();
        for (int i = 0; i < N; i++) {
            cin >> s;
            root->insert_word(s,0);
        }
        cin >> Q;
        for (int i = 0; i < Q; i++) {
            cin >> s;
            bool f = root->search_word(s,0);
            if(f == false) printf("Found\n");
            else printf("Not Found\n");
        }
        root->delete_trie();
        delete root;
    }
    return 0;
}
