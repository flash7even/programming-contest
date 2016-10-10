#include <bits/stdc++.h>
using namespace std;

#define Max 1000000
int phi[Max];

void euler_phi(){
	phi[1] = 1;
	for(int i = 2;i<Max;i++){
		if(!phi[i]){
			phi[i] = i-1;
			for(int j = (i<<1);j<Max;j+=i){
				if(!phi[j]){
					phi[j] = j;
				}
				phi[j] = phi[j]/i*(i-1);
			}
		}
	}

}

int main() {
	euler_phi();
	for(int i= 1;i<=50;i++){
		printf("i: %d = %d\n",i,phi[i]);
	}
}
