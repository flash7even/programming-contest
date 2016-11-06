/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

/**
    Given a matrix and some knights with their positions.
    Some possible moves are also given.
    A player can move any knight from it's cell using any given possible move.
    Last player who gives move win.
**/


#define Size 100005

int N;
int DP[1055][1055];
int dx[] = {1, -1, -1, -2, -3, -2};
int dy[] = {-2, -3, -2, -1, -1, 1};

bool isValid(int R,int C){
    if(R<0 || C<0 || R>=1055 || C>=1055) return false;
    return true;
}

int call(int R,int C){
    //pf("Cur R: %d , C: %d\n",R,C);
    if(R == 0 && C == 0) return 0;
    if(DP[R][C] != -1) return DP[R][C];
    vector<int> grundy;
    for(int i = 0; i < 6; i++) {
        int nR = R + dx[i];
        int nC = C + dy[i];
        if(isValid(nR,nC) == false) continue;
        grundy.pb(call(nR,nC));
    }
    make_unique(grundy);
    if(grundy.size() == 0) return DP[R][C] = 0;
    if(grundy[0] != 0) return DP[R][C] = 0;
    int f = 0;
    for(int i = 1;i<grundy.size();i++){
        if(grundy[i] == f) continue;
        f++;
        if(grundy[i] != f) return DP[R][C] = f;
    }
    return DP[R][C] = grundy[grundy.size()-1] + 1;
}

int main(){
    int nCase,x,y;
    sf("%d",&nCase);
    mems(DP,-1);
    for(int cs = 1;cs<=nCase;cs++){
        sf("%d",&N);
        int res = 0;
        for(int i = 0;i<N;i++){
            sf("%d %d",&x,&y);
            res = res ^ call(x,y);
        }
        if(res == 0) pf("Case %d: Bob\n",cs);
        else pf("Case %d: Alice\n",cs);
    }
    return 0;
}
