#include <bits/stdc++.h>
using namespace std;

struct node {
    node *ch[2];
    int r,v,s;
    node(int v):v(v) {
        s = 1;
        r = rand();
        ch[0] = ch[1] = NULL;
    }
    bool operator <(const node &rhs) const {
        return r<rhs.r;
    }
    int cmp(int x) {
        if(x == v) return -1;
        return x<v ? 0:1;
    }
    void maintain() {
        s = 1;
        if(ch[0] != NULL) s += ch[0]->s;
        if(ch[1] != NULL) s += ch[1]->s;
    }
};

struct Treap {
    inline void rotate(node * &o,int d) {
        node *k = o->ch[d^1];
        o->ch[d^1] = k->ch[d];
        k->ch[d] = o;
        o->maintain();
        k->maintain();
        o = k;
    }

    inline void insert(node * &o,int x) {
        if(o == NULL) o = new node(x);
        else{
            int d = (x<o->v ? 0:1);
            insert(o->ch[d],x);
            if(o->ch[d]->r>o->r) rotate(o,d^1);
        }
        o->maintain();
    }

    inline void remove(node * &o,int x) {
        int d = o->cmp(x);
        if(d == -1) {
            node *u = o;
            if(o->ch[0] != NULL && o->ch[1] != NULL) {
                int d2 = (o->ch[0]->r>o->ch[1]->r? 1:0);
                rotate(o,d2);
                remove(o->ch[d2],x);
            } else {
                if(o->ch[0] == NULL) o = o->ch[1];
                else o = o->ch[0];
                delete u;
            }
        }
        else {
            remove(o->ch[d],x);
        }
        if(o != NULL) o->maintain();
    }

    inline int kth(node * o,int k) {
        if(o == NULL || k <= 0 || k>o->s) return 0;
        int s = (o->ch[0] == NULL ? 0: o->ch[0]->s);
        if(k == s+1) return o->v;
        else if(k <= s) return kth(o->ch[0],k);
        else return kth(o->ch[1],k-s-1);
    }
}treap;

/// While using treap, always remember to use root in the function parameter.

int main () {
    int A[] = {2,4,7,1,2,22,5,15,5,2};

	node *root = NULL;
    for(int i = 0;i<10;i++){
        treap.insert(root,A[i]);
    }

    /// treap.remove(root,2); /// remove only one occurrence of 2

    for(int i = 1;i<=10;i++){
        /// Find the i'th element in sorted order(1 based index)
        int kth = treap.kth(root,i);
        printf("%d'th num = %d\n",i,kth);
    }
    return 0;
}
