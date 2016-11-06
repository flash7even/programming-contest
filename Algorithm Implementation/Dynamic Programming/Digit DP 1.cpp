/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

#define Size 100005
#define Mod 1000000007

/**
    Problem : A number is d magic if at all the position there's d not any where else.
              Find number of d magic numbers between u and v.
    Algorithm : Digit DP
    Link : http://codeforces.com/contest/628/problem/D
**/

int M,D,N;
int DP[2005][2005][3][3];
string u,v;

int call(int cur,int mod,int f1,int f2){
    if(cur == N){
        return (mod == 0);
    }
    int &ret = DP[cur][mod][f1][f2];
    if(ret != -1) return ret;

    ret = 0;
    int lo,hi;
    /// 1 means we are at the last limit in previous digit.
    if(f1 == 1) lo = u[cur] - '0';
    else lo = 0;
    if(f2 == 1) hi = v[cur] - '0';
    else hi = 9;

    /// When current digit == lo , we are at lower limit.
    /// When current digit == hi , we are at higher limit.

    if((cur+1) % 2 == 0){
        /// We must place D at even position.
        if(D>=lo && D<=hi) ret = ret + call(cur+1,(mod*10 + D)%M,f1 && (D == lo),f2 && (D == hi));
        ret %= Mod;
    }else{
        for(int d = lo;d<=hi;d++){
            if(d == D) continue; /// We can't place D at even position.
            ret = ret + call(cur+1,(mod*10 + d)%M,f1 && (d == lo),f2 && (d == hi));
            ret %= Mod;
        }
    }
    return ret;
}

int main(){
    cin >> M >> D;
    cin >> u >> v;
    N = v.length();
    mems(DP,-1);
    int res = call(0,0,1,1);
    cout << res << endl;
	return 0;
}
