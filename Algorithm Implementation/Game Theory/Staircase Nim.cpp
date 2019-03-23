/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

/**
    Given a tree and coins in each vertex.
    A player can move any no of coins to it's parent vertex.
    Last player move wins.
    In this problem for query a parent can be changed in the tree.
**/


#define Size 100005

int n, cnt, q, uu, vv;
int st[100005], en[100005], color[100005], parent[100005];
int whiteXor[100005], blackXor[100005], c[100005];
vector<int> Graph[100005];

void dfs(int pos, int par, int colr) {
    cnt++;
    st[pos] = cnt;
    color[pos] = colr;
    parent[pos] = par;

    if(colr == 0) whiteXor[pos] = c[pos];
    else blackXor[pos] = c[pos];

    for (int i=0; i<Graph[pos].size(); i++) {
        int j = Graph[pos][i];
        if (j == par) continue;
        dfs(j,pos,colr^1);
        blackXor[pos] ^= blackXor[j];
        whiteXor[pos] ^= whiteXor[j];
    }
    en[pos] = cnt;
    return;
}

int main () {
    scanf("%d", &n);
    for (int i=1; i<=n; i++) {
        scanf("%d", &c[i]);
    }
    for (int i=2; i<=n; i++) {
        scanf("%d %d", &uu, &vv);
        Graph[uu].pb(vv);
        Graph[vv].pb(uu);
    }
    cnt = 0;
    dfs(1,1,1);
    scanf("%d", &q);
    while (q--) {
        scanf("%d %d", &uu, &vv);
        if ( st[uu] <= st[vv] && en[uu] >= en[vv] ) {
            printf("INVALID\n");
        } else {
            int cww = whiteXor[1], cbb = blackXor[1];
            if (color[parent[uu]] == color[vv]) {
                if (cww > 0) {
                    printf("YES\n");
                } else {
                    printf("NO\n");
                }
            } else {
                cww ^= whiteXor[uu];
                cww ^= blackXor[uu];
                if (cww > 0) {
                    printf("YES\n");
                } else {
                    printf("NO\n");
                }
            }
        }
    }
    return 0;
}
