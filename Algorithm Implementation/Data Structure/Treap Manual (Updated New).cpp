#include <bits/stdc++.h>
using namespace std;

struct node {
    int v, key, size;
    node *c[2];
    void resize() {
        size = c[0]->size + c[1]->size + 1;
    }
};

vector<node> treapTree; /// Never access this array. Only treap access this internally.

node *newNode(int _v, node *n) {
    node leaf;
    leaf.v = _v, leaf.c[0] = leaf.c[1] = n, leaf.size = 1, leaf.key = rand();
    treapTree.push_back(leaf);
    return &treapTree[treapTree.size()-1];
}

/// NOTE: Always pass the root as function parameter.

struct Treap {
    node *root, *nil;

    void rotate(node *&t, int d) { /// Internal function.
        node *c = t->c[d];
        t->c[d] = c->c[!d];
        c->c[!d] = t;
        t->resize(); c->resize();
        t = c;
    }

    void insert(node *&t, int x) { /// Insert an element.
        if (t == nil) t = newNode(x, nil);
        else {
            if (x == t->v) return;
            int d = x > t->v;
            insert(t->c[d], x);
            if (t->c[d]->key < t->key) rotate(t, d);
            else t->resize();
        }
    }

    void remove(node *&t, int x) { /// Remove an element.
        if (t == nil) return;
        if (t->v == x) {
            int d = t->c[1]->key < t->c[0]->key;
            if (t->c[d] == nil) {
                t = nil;
                return;
            }
            rotate(t, d);
            remove(t->c[!d], x);
        } else {
            int d = x > t->v;
            remove(t->c[d], x);
        }
        t->resize();
    }

    int rankOfElement(node *t, int x) { /// Returns number of elements <= x.
        if (t == nil) return 0;
        int r = t->c[0]->size;
        if (x == t->v) return r + 1;
        if (x < t->v) return rankOfElement(t->c[0], x);
        return r + 1 + rankOfElement(t->c[1], x);
    }

    int kthElement(node *t, int k) { /// Returns k'th element(1 based).
        int r = t->c[0]->size;
        if (k == r + 1) return t->v;
        if (k <= r) return kthElement(t->c[0], k);
        return kthElement(t->c[1], k - r - 1);
    }

    int size() { /// Returns number of elements in the treap.
        return root->size;
    }

    void clear() { /// Clear the treap.
        treapTree.clear();
        nil = newNode(0, 0);
        nil->size = 0, nil->key = ~0U >> 1;
        root = nil;
    }

    void printTreap(){ /// Print all the elements in sorted order.
      cout << "TREAP: ";
      for(int i = 1;i<=size();i++){
            cout << " " << kthElement(root, i);
      }
      cout << endl;
    }
};

int main () {

    Treap treap;
    treap.clear();

    treap.insert(treap.root, 1e9);
    treap.insert(treap.root, 25);
    treap.insert(treap.root, 1e8);
    treap.insert(treap.root, 55);
    treap.insert(treap.root, 55);
    treap.insert(treap.root, 33);
    treap.insert(treap.root, 1e7);
    treap.insert(treap.root, 2);
    treap.insert(treap.root, 22);
    treap.insert(treap.root, 5);
    printf("SIZE: %d\n",treap.size());
    treap.printTreap();
    printf("Rank of %d = %d\n",30,treap.rankOfElement(treap.root, 30));
    printf("Rank of %d = %d\n",50,treap.rankOfElement(treap.root, 50));
    printf("Rank of %d = %d\n",15,treap.rankOfElement(treap.root, 15));
    printf("Rank of %d = %d\n",15,treap.rankOfElement(treap.root, 22));
    treap.remove(treap.root, 25);
    treap.remove(treap.root, 33);
    treap.clear();
    printf("SIZE: %d\n",treap.size());
    treap.printTreap();
    treap.insert(treap.root, 44);
    treap.insert(treap.root, 77);
    treap.insert(treap.root, 11);
    printf("SIZE: %d\n",treap.size());
    treap.printTreap();
    printf("Rank of %d = %d\n",30,treap.rankOfElement(treap.root, 30));
    printf("Rank of %d = %d\n",50,treap.rankOfElement(treap.root, 50));
    printf("Rank of %d = %d\n",15,treap.rankOfElement(treap.root, 15));
    treap.insert(treap.root, 10);
    treap.insert(treap.root, 25);
    treap.insert(treap.root, 5);
    treap.insert(treap.root, 55);
    treap.insert(treap.root, 33);
    treap.insert(treap.root, 2);
    treap.insert(treap.root, 22);
    printf("SIZE: %d\n",treap.size());
    treap.printTreap();
    printf("Rank of %d = %d\n",30,treap.rankOfElement(treap.root, 30));
    printf("Rank of %d = %d\n",50,treap.rankOfElement(treap.root, 50));
    printf("Rank of %d = %d\n",15,treap.rankOfElement(treap.root, 15));
    return 0;
}
