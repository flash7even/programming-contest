/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

LL fact[30];
LL cnt[30];
string s;
char ans[30];
int N,K;
bool fnd = false;

void call(int rem,int cur){
    if(cur == N){
        ans[cur] = '\0';
        pf("%s\n",ans);
        fnd = true;
        return;
    }
    LL prvCnt = 0;
    for(int d = 0;d<26;d++){
        if(fnd == true) return;
        if(cnt[d] == 0) continue;
        cnt[d]--;
        LL curCnt = fact[N-cur-1];
        for(int v = 0;v<26;v++){
            curCnt /= fact[cnt[v]];
        }
        curCnt = curCnt + prvCnt;
        if(rem<curCnt && rem>=prvCnt){
            ans[cur] = ('a' + d);
            call(rem - prvCnt,cur+1);
            if(fnd == true) return;
        }else{
            cnt[d]++;
            prvCnt = curCnt;
        }
    }
}

int main(){

    fact[0] = 1;
    for(LL i = 1;i<22;i++) fact[i] = i*fact[i-1];

	int nCase;
	cin >> nCase;
	for(int cs = 1;cs<=nCase;cs++){
		cin >> s >> K;
		mems(cnt,0);
		N = s.length();
		for(int i = 0;i<N;i++){
            int d = (int)(s[i]-'a');
            cnt[d]++;
		}
		fnd = false;
		pf("Case %d: ",cs);
		call(K-1,0);
		if(fnd == false) pf("Impossible\n");
	}
	return 0;
}
