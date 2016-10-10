#include <bits/stdc++.h>
using namespace std;

#define Size 100005
#define Max 100005
#define INF (1<<30)
#define Mod 1000000007

bool mark[Size];
vector <int> pL;
int totalPrime = 0;

void seive(){
    memset (mark, true, sizeof (mark));
    mark [0] = mark [1] = false;
    for(int i = 4;i<Size;i+=2) mark [i] = false;
    for(int i=3;i*i<=Size;i+=2){
        if(mark[i]){
            for(int j=i*i;j<Size;j+=2*i)
                mark [j] = false;
        }
    }
    pL.clear ();
    pL.push_back (2);
    for(int i=3;i<Size;i+=2){
        if(mark[i]){
            pL.push_back (i);
        }
    }
    totalPrime = pL.size();
}

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

int main() {

}
