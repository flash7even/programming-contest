/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

/**
    Given a string of dot and X.
    XXX is winning position.
    A player can place an X at any dot position.
**/


#define Size 100005

int N;
int DP[255];
vector<int> res;
string s;

int call(int cur){
    if(cur <= 0) return DP[cur] = 0;
    if(DP[cur] != -1) return DP[cur];
    vector<int> grundy;

    for(int p = 0;p<=cur/2;p++){
        int d1 = p - 2,d2 = cur - p - 2 - 1;
        grundy.push_back(call(d1) ^ call(d2));
    }

    make_unique(grundy);
    if(grundy.size() == 0 || grundy[0] != 0) return DP[cur] = 0;
    int f = 0;
    for(int i = 1;i<grundy.size();i++){
        if(grundy[i] == f) continue;
        f++;
        if(grundy[i] != f) return DP[cur] = f;
    }
    return DP[cur] = grundy[grundy.size()-1] + 1;
}

bool isPossible(int pos){
    string ss = s;
    if(ss[pos] == 'X') return false;
    ss[pos] = 'X';
    for(int i = 1;i<N-1;i++){
        if(ss[i] == 'X'){
            if(ss[i-1] == 'X' && ss[i+1] == 'X') return true;
        }
    }
    for(int i = 1;i<N-1;i++){
        if(ss[i] == 'X'){
            if(ss[i-1] == 'X' || ss[i+1] == 'X') return false;
        }else if(ss[i] == '.'){
            if(ss[i-1] == 'X' && ss[i+1] == 'X') return false;
        }
    }
    int i = 0,lastX = -1;
    int xorr = 0;
    while(i<N){
        if(ss[i] == 'X'){
            int cnt = i - lastX - 2 - 1;
            xorr = xorr ^ call(cnt);
            lastX = i;
            i++;
            break;
        }
        i++;
    }
    while(i<N){
        if(ss[i] == 'X'){
            int cnt = i - lastX - 2 - 2 - 1;
            xorr = xorr ^ call(cnt);
            lastX = i;
        }
        i++;
    }
    int cnt = i - lastX - 2 - 1;
    xorr = xorr ^ call(cnt);
    if(xorr == 0) return true;
    return false;
}

int main(){
    fast_cin;
    mems(DP,-1);
    int nCase;
    cin >> nCase;
    for(int cs = 1;cs<=nCase;cs++){
        cin >> s;
        N = s.length();
        res.clear();
        for(int i = 0;i<N;i++){
            if(isPossible(i) == true){
                res.pb(i+1);
            }
        }
        pf("Case %d:",cs);
        int Sz = res.size();
        for(int i = 0;i<Sz;i++){
            pf(" %d",res[i]);
        }
        if(Sz == 0) pf(" 0\n");
        else pf("\n");
    }
    return 0;
}
