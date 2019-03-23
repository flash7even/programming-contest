/// Implicit Treap Implementation
/// Can handle most of the operations we do in segment tree
/// Ex: Range update, range query
/// Additionally also handles insert or erase at any position, reverse a range
/// Call clear() to clear the treap, then use each function carefully following the comments
/// If there is propagation, uncomment propagate() inside the functions
/// Note 1: All the operations are zero based
/// Note 2: Remember to propagate if you try to access the treap nodes outside split and merge

struct node{
    int size, prior;
    int sum, prop, key, mnn;
    bool rev;
    struct node *l, *r;
    node() { }
    node(int v) {
        key = v;
        prior = rand();
        size = 1;
        l = r = NULL;
        sum = prop = 0;
        mnn = inf;
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

    int sum(pnode t){
        return t ? t->sum:0;
    }

    int mnn(pnode t){
        return t ? t->mnn:inf;
    }

    void upd_node(pnode t){
        if(t){
            t->size = sz(t->l) + 1 + sz(t->r);
            //t->sum = sum(t->l) + t->key + sum(t->r); /// If you need sum
            t->mnn = min(t->key, min(mnn(t->l), mnn(t->r)));
        }
    }

    /// Works like segment tree propagation
    void propagate(pnode t){
        if(!t) return;
        if(t->prop>0){ /// Propagate range addition
            if(t->l){
                t->l->key += t->prop;
                t->l->sum += sz(t->l)*t->prop;
                t->l->prop += t->prop;
                t->l->mnn += t->prop;
            }
            if(t->r){
                t->r->key += t->prop;
                t->r->sum += sz(t->r)*t->prop;
                t->r->prop += t->prop;
                t->r->mnn += t->prop;
            }
            t->prop = 0;
        }
        if(t->rev){ /// Propagate range reverse
            swap(t->l, t->r);
            if(t->l) t->l->rev ^= true;
            if(t->r) t->r->rev ^= true;
            t->rev = false;
        }
    }

    /// Split t into l and r such that all elements in l is < key and
    /// all elements in r is >= than key
    void split(pnode t, pnode &l, pnode &r, int key, int add = 0){
        if(!t){
            l = r = NULL;
            return;
        }
        propagate(t);
        int cur_key = add + sz(t->l);
        if(cur_key < key)
            split(t->r, t->r, r, key, add + 1 + sz(t->l)), l = t;
        else
            split(t->l, l, t->l, key, add), r = t;
        upd_node(t);
    }

    /// Merge l and r into t, where all elements in l
    /// is less than all elements in r
    void merge(pnode &t, pnode l, pnode r){
        propagate(l);
        propagate(r);
        if(!l || !r) t = l ? l:r;
        else if(l->prior > r->prior) merge(l->r, l->r, r), t = l;
        else merge(r->l, l, r->l), t = r;
        upd_node(t);
    }

    void insert(pnode &t, int pos, pnode it){
        pnode l, r, tmp;
        split(t, l, r, pos);
        merge(tmp, l, it);
        merge(t, tmp, r);
        upd_node(t);
    }

    void insertEnd(pnode &t, pnode it){
        pnode l, r, tmp;
        merge(t, t, it);
        upd_node(t);
    }

    void erase(pnode &t, int key){
        pnode t1, t2, nt1, nt2;
        split(t, t1, t2, key+1);
        split(t1, nt1, nt2, key);
        merge(t, nt1, t2);
        upd_node(t);
        free(nt2);
    }

    int get(pnode &t, int key, int add = 0){
        if(!t) return 0;
        propagate(t);
        int cur_key = add + sz(t->l);
        if(cur_key == key){
            return t->key;
        }else{
            if(cur_key < key) return get(t->r, key, add + 1 + sz(t->l));
            else return get(t->l, key, add);
        }
        upd_node(t);
    }

    void print(pnode t){
        if(!t) return;
        propagate(t);
        print(t->l);
        cerr << t->key << " ";
        print(t->r);
    }

    void nullify(pnode t){
        if(t == NULL) return;
        nullify(t->l); nullify(t->r);
        delete t;
        t->l = NULL; t->r = NULL; t = NULL;
        free(t);
    }

    /// Insert val at position p in the treap
    void insert(int p, int val){
        pnode it = new node(val);
        insert(t, p, it);
    }

    /// Insert val at the end of the treap
    void insertEnd(int val){
        pnode it = new node(val);
        insertEnd(t, it);
    }

    /// Erase the element at p from the treap
    void erase(int p){
        erase(t, p);
    }

    /// Returns the value at position p
    int get(int p){
        return get(t, p);
    }

    /// Print all the elements in treap in sorted order
    void print(){
        cerr<<"\nPRINT TREAP: ";
        print(t);
        cerr<<" \n";
    }

    /// Clear the treap
    void clear(){
        nullify(t);
        t = NULL;
    }

    /// Get the minimum in range u to v
    int getRangeMin(int u, int v){
        pnode tv, tvn, tu, tuv;
        split(t, tv, tvn, v+1);
        split(tv, tu, tuv, u);

        int res = min(tuv->key, min(mnn(tuv->l), mnn(tuv->r)));
        merge(tv, tu, tuv);
        merge(t, tv, tvn);
        return res;
    }

    /// Get the sum of range u to v
    int getRangeSum(int u, int v){
        pnode tv, tvn, tu, tuv;
        split(t, tv, tvn, v+1);
        split(tv, tu, tuv, u);

        int res = tuv->sum;
        merge(tv, tu, tuv);
        merge(t, tv, tvn);
        return res;
    }

    /// Rotate(right) the range from u to v k times
    void updateRangeRotate(int u, int v, int k){
        pnode tv, tvn, tu, tuv;
        split(t, tv, tvn, v+1);
        split(tv, tu, tuv, u);

        int len = v - u + 1;
        k %= len;

        pnode tuv1, tuv2;
        split(tuv, tuv1, tuv2, len-k);

        merge(tuv, tuv2, tuv1);
        merge(tv, tu, tuv);
        merge(t, tv, tvn);
    }

    /// Reverse the range from u to v
    void updateRangeReverse(int u, int v){
        pnode tv, tvn, tu, tuv;
        split(t, tv, tvn, v+1);
        split(tv, tu, tuv, u);

        tuv->rev ^= true;

        merge(tv, tu, tuv);
        merge(t, tv, tvn);
    }

    /// Add val to each node in range u to v
    void updateRangeAdd(int u, int v, int val){
        pnode tv, tvn;
        split(t, tv, tvn, v+1);

        pnode tu, tuv;
        split(tv, tu, tuv, u);

        tuv->key += val;
        tuv->sum += sz(tuv)*val;
        tuv->prop += val;

        merge(tv, tu, tuv);
        merge(t, tv, tvn);
    }

}treap;
