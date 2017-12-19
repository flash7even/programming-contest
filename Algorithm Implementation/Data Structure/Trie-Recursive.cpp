/// Trie Recursion Based Implementation
/// Create the root (root = new Trie())
/// Use insert and search accordingly
/// At the end call delete_trie() to delete all the nodes

class Trie {
    bool ed;
    Trie *child[10];
    /// If ed is true, a word finished here.

public:
    Trie() {
        ed = false;
        for (int i = 0; i < 10; i++){
            child[i] = NULL;
        }
    }

    /// Delete to save memory.
    void delete_trie() {
        for (int i = 0; i < 10; i++)
            if (child[i] != NULL) {
                child[i]->delete_trie();
                delete child[i];
            }
    }

    void insert(string &word, int pos) {
        if (pos == (int)word.length()){
            ed = true; /// A valid string ends here.
        }
        int c = (int)(word[pos] - '0');
        if (child[c] == NULL) {
            child[c] = new Trie();
        }
        return child[c]->insert(word, ++pos);
    }

    bool search(string &word, int pos) {
        if (pos == (int)word.length()) return ed;
        int c = (int)(word[pos] - '0');
        if (child[c] == NULL) return false;
        return child[c]->search(word, ++pos);
    }

}*root;
