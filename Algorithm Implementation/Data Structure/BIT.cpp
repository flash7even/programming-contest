#include <bits/stdc++.h>
using namespace std;
#define Size 1000005

int A[Size];
int bit_tree[Size];
int N;

void update_tree(int idx,int val){
	while(idx <= N){
		bit_tree[idx] += val;
		idx = idx + (idx & (-idx));
	}
}

int query_tree(int idx){
	int sum = 0;
	while(idx > 0){
		sum += bit_tree[idx];
		idx = idx - (idx & (-idx));
	}
	return sum;
}

void initialize(){
	memset(bit_tree,0,sizeof(bit_tree));
}

int main() {
	scanf("%d",&N);
	for(int i = 1;i<=N;i++){
		scanf("%d",&A[i]);
	}
	return 0;
}
