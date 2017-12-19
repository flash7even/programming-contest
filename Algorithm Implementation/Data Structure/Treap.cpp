/// Treap which support multiple entry, works like a multiset
/// If you want to use like a set then just erase the element before insert
/// All the functions are similar to the built in treap
/// Every function works in log(N) except unite()

struct node{
    int key, prior, size;
    struct node *l, *r;
    node() { }
    node(int v) {
        key = v;
        prior = rand();
        size = 1;
        l = r = NULL;
    }
    node (int key, int prior) : key(key), prior(prior), l(NULL), r(NULL) { }
};

typedef node* pnode;

struct Treap{
    pnode t;
    Treap(){}

    /// Returns size of treap
    int size(){
        return sz(t);
    }

    int sz(pnode t){
        return t ? t->size:0;
    }

    void upd_sz(pnode t){
        if(t) t->size = sz(t->l) + 1 + sz(t->r);
    }

    /// Split t into l and r such that all elements in l
    /// is less than key and all elements in r is greater than key
    void split(pnode t, pnode &l, pnode &r, int key){
        if(!t) l = r = NULL;
        else if(t->key < key) split(t->r, t->r, r, key), l = t;
        else split(t->l, l, t->l, key), r = t;
        upd_sz(t);
    }

    /// Merge l and r into t, where all elements in l
    /// is less than all elements in r
    void merge(pnode &t, pnode l, pnode r){
        if(!l || !r) t = l ? l:r;
        else if(l->prior > r->prior) merge(l->r, l->r, r), t = l;
        else merge(r->l, l, r->l), t = r;
        upd_sz(t);
    }

    /// Unite two different treap l and r into a new treap
    /// Complexity O(N)
    pnode unite (pnode l, pnode r) {
        if (!l || !r)  return l ? l : r;
        if (l->prior < r->prior)  swap (l, r);
        pnode lt, rt;
        split (r, lt, rt, l->key);
        l->l = unite (l->l, lt);
        l->r = unite (l->r, rt);
        return l;
    }

    void insert(pnode &t, pnode it){
        if(!t) t = it;
        else if(it->prior > t->prior) split(t, it->l, it->r, it->key), t = it;
        else insert(t->key < it->key ? t->r:t->l, it);
        upd_sz(t);
    }

    void erase(pnode &t, int key){
        if(!t) return;
        else if(t->key == key){
            pnode temp = t; merge(t, t->l, t->r); free(temp);
        }else{
            erase(t->key < key ? t->r:t->l,key);
        }
        upd_sz(t);
    }

    void init(pnode &t, int c){
        t->prior = rand(); t->size = 1;  t->l = t->r = NULL;
        t->key = c;
    }

    void print(pnode t){
        if(!t) return;
        print(t->l);
        cerr << t->key << " " << endl;
        print(t->r);
    }

    int getKth(pnode temp, int par, int k){
        if(temp == NULL) return 0;
        int currSize = par + sz(temp->l)  + 1;
        if(currSize == k) return temp->key;

        else if(currSize <= k) return getKth(temp->r, currSize, k);
        else return getKth(temp->l, par, k);
    }

    int orderOf(pnode temp, int k){
        int x = 0;
        if(temp == NULL) return 0;
        if(temp->key < k) return sz(temp->l) + 1 + orderOf(temp->r, k);
        else return orderOf(temp->l, k);
    }

    void nullify(pnode t){
        if(t == NULL) return;
        nullify(t->l); nullify(t->r);
        delete t;
        t->l = NULL; t->r = NULL; t = NULL;
        free(t);
    }

    /// Insert k in the treap
    void insert(int k){
        pnode it = new node(k);
        insert(t, it);
    }

    /// Erase k for the treap
    void erase(int k){
        erase(t, k);
    }

    /// Returns the k'th smallest element in treap(0 based)
    int find_by_order(int k){
        return getKth(t, 0, k+1);
    }

    /// Returns number of elements less than k
    int order_of_key(int k){
        return orderOf(t, k);
    }

    /// Print all the elements in treap in sorted order
    void print(){
        cerr<<"\nPRINT TREAP: ";
        print(t);
        cerr<<" \n\n";
    }

    /// Clear the treap
    void clear(){
        nullify(t);
        t = NULL;
    }

}treap;
