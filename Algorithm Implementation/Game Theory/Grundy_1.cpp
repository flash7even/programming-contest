/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

/**
    Initially there are n piles.
    A pile is formed by some cells.
    Alice starts the game and they alternate turns.
    In each tern a player can pick any pile and divide it into two unequal piles.
    If a player cannot do so, he/she loses the game.
**/

#define Size 100005

int N;
int A[105];
int DP[10005];

int call(int cur){
    if(cur <= 2) return 0;
    if(DP[cur] != -1) return DP[cur];
    vector<int> grundy;
    for(int d1 = 1;d1<=cur/2;d1++){
        int d2 = cur-d1;
        if(d1 != d2){
            grundy.pb(call(d1) ^ call(d2));
        }
    }
    make_unique(grundy);
    if(grundy[0] != 0) return DP[cur] = 0;
    int f = 0;
    for(int i = 1;i<grundy.size();i++){
        if(grundy[i] == f) continue;
        f++;
        if(grundy[i] != f) return DP[cur] = f;
    }
    return DP[cur] = grundy[grundy.size()-1] + 1;
}

int main(){
    int nCase;
    sf("%d",&nCase);
    mems(DP,-1);
    for(int cs = 1;cs<=nCase;cs++){
        sf("%d",&N);
        int res = 0;
        for(int i = 0;i<N;i++){
            sf("%d",&A[i]);
            res = res ^ call(A[i]);
        }
        if(res == 0) pf("Case %d: Bob\n",cs);
        else pf("Case %d: Alice\n",cs);
    }
    return 0;
}
