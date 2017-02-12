struct node {
    int cnt;
    int child[55];
};

node T[Size];

struct trie {

    int id;

    void createNode() {
        T[id].cnt = 0;
        memset(T[id].child, -1, sizeof T[id].child);
        id++;
    }

    void initialize() {
        id = 0;
        createNode();
    }

    int FID(const char &c){
      if(c >= 'A' && c <= 'Z') return c - 'A';
      else return (c - 'a') + 26;
    }

    void insert_word(const string &s) {
        int cur = 0;
        T[cur].cnt++;
        for (int i = 0; i < s.size(); ++i) {
            int id = FID(s[i]);
            if (T[cur].child[id] == -1) {
                T[cur].child[id] = id;
                createNode();
            }
            cur = T[cur].child[id];
            T[cur].cnt++;
        }
    }

    int search_word(const string &s) {
        int cur = 0;
        for (int i = 0; i < s.size(); ++i) {
            int id = FID(s[i]);
            if (T[cur].child[id] == -1)  return 0;
            cur = T[cur].child[id];
        }
        return T[cur].cnt;
    }
};

trie root;
