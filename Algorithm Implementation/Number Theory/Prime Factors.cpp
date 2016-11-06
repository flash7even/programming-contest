#include <bits/stdc++.h>
using namespace std;

vector<int> pfList;
map<int,int> pfCnt;

void prime_Factor(int num){
	for(int i = 0;i<totalPrime;i++){
		int fctor = pL[i];
		if(fctor*fctor>num) break;
		if(num%fctor == 0){
			pfList.pb(fctor);
			while(num%fctor == 0){
				pfCnt[fctor]++;
				num /= fctor;
			}
		}
	}
	if(num>1){
		pfList.pb(num);
		pfCnt[num]++;
	}
}
