/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

/**
    Initially there are n piles.
    A pile is formed by some stones.
    Alice starts the game and they alternate turns.
    In each tern a player can pick any pile and remove some stones.
    At least 1 and at most half of stones on that pile.
    If a player cannot do so, he/she loses the game.
**/

#define Size 100005

int N;
int A[1005];
int DP[10005];

int call(int cur){
    if(cur%2 == 0) return cur/2;
    while(cur%2 != 0) cur/=2;
    return cur/2;
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
