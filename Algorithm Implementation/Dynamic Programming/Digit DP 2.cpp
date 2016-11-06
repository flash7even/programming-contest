/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

#define Mod 1000000007
#define Max 150000

/**
    Problem : Given u and v we have to find number of palindrome numbers between them.
    Algorithm : Digit DP
    Link : http://lightoj.com/volume_showproblem.php?problem=1205
**/

LL u,v;
int digit[20];
int taken[20];
LL DP[20][20][3][3];

LL call(int cur,int len,int st,int f){
    if(cur == 0) return 1;
    if(DP[cur][len][f][st] != -1) return DP[cur][len][f][st];

    int mxDigit = 9;
    if(f == 1) mxDigit = digit[cur];
    LL res = 0;
    /// Depending on the f we decide the max digit we can place.

    for(int d = 0;d<=mxDigit;d++){
        taken[cur] = d;
        if(st == 0){
            if(d == 0){
                // If first digit is zero then it'll decrease the length.
                res += call(cur-1,len-1,st,(f&&(d==mxDigit)));
            }else{
                res += call(cur-1,len,1,(f&&(d==mxDigit)));
            }
        }else{
            /// For handling palindrome.
            int mid = (len+1)/2;
            bool small = false;

            if(len%2 == 0){
                if(cur <= mid) small = true;
            }else{
                if(cur < mid) small = true;
            }

            if(small == true){
                if(d == taken[len + 1 - cur]){
                    res += call(cur-1,len,st,(f&&(d==mxDigit)));
                }
            }else{
                res += call(cur-1,len,st,(f&&(d==mxDigit)));
            }
        }
    }
    if(f == 0) return DP[cur][len][f][st] = res;
    else return res;
}

LL solve(LL val){
    int cnt = 0;
    while(val){
        digit[++cnt] = val % 10;
        val /= 10;
    }
    return call(cnt,cnt,0,1);
}

int main(){
    int nCase;
    sf("%d",&nCase);
    for(int cs = 1;cs<=nCase;cs++){
        mems(DP,-1);
        sf("%lld %lld",&u,&v);
        if(u>v) swap(u,v);
        LL res = solve(v) - solve(u-1);
        pf("Case %d: %lld\n",cs,res);
    }
    return 0;
}
