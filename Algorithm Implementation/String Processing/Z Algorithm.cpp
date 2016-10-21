#include <bits/stdc++.h>
using namespace std;

/// Calculate the Z array.
/// Z[i] = maximum length of substring that starts
/// at index i and is also the prefix of s.

string s;
int Z[1000005];
int N;

void getZarray(string s,int N){
    int L = 0,R = 0;
    for(int i = 1;i<N;i++){
        if(i>R){
            L = R = i;
            while(R<N && s[R-L] == s[R]){
                R++;
            }
            Z[i] = R-L;
            R--;
        }else{
            int k = i - L;
            if(Z[k]<R-i+1){
                Z[i] = Z[k];
            }else{
                L = i;
                while(R<N && s[R-L] == s[R]){
                    R++;
                }
                Z[i] = R-L;
                R--;
            }
        }
    }
    Z[0] = N;
}

int main() {
    int nCase,idx;
    cin >> nCase;
    for(int cs = 1;cs<=nCase;cs++){
        cin >> s;
        N = s.length();
        getZarray(s,N);
    }
    return 0;
}
