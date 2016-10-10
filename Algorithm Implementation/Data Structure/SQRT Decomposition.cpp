#include <bits/stdc++.h>
using namespace std;
#define INF 99999999

/**
   Square Root Decomposition
   Given the values of an array.There will be 2 kind of operations.
     1. Change the value at any given index.
     2. Given u & v, find lowest value from index u to index v in the array .
   Time complexity for update and query operation O ( sqrt( N ) )
**/

const int blockSize = 600;
/// It'll be sqrt of total elements.
/// Mat vary depending on number of query operations.

int A[1000010];
int BLOCK[600];

int get_ID(int index) {
	return index / blockSize;
}

void update(int u, int val) {
	A[u] = val;
	int id = get_ID(u);
	int start = id * blockSize;
	int ed = (id + 1) * blockSize - 1;

	for (int i = start; i <= ed; i++) {
		if (i == start){
			BLOCK[id] = A[i];
		}else{
			BLOCK[id] = min(BLOCK[id], A[i]);
		}
	}
}

int query(int L, int R) {
	int id1 = get_ID(L); /// left id
	int id2 = get_ID(R); /// right id

	if (id1 == id2) {
		int mn = INF;
		for (int i = L; i <= R; i++){
			mn = min(mn, A[i]);
		}
		return mn;
	}

	int mn1 = INF, mn2 = INF, mn3 = INF;

	for (int i = L; i <= id1 * blockSize + blockSize - 1; i++){
		mn1 = min(mn1, A[i]);
	}
	for (int i = id1 + 1; i < id2; i++){
		mn2 = min(mn2, BLOCK[i]);
	}
	for (int i = id2 * blockSize; i <= R; i++){
		mn3 = min(mn3, A[i]);
	}
	return min(min(mn1, mn3), mn2);
}

int main() {
	int N, Q, a, typ, x, y;
	scanf("%d %d", &N, &Q);
	for (int i = 0; i < N; i++) {
		scanf("%d", &a);
		update(i, a);
	}
	/// 0 based index.
	for(int i = 0;i<Q;i++){
		scanf("%d %d %d", &typ, &x, &y);
		if (typ == 1) {
			update(x - 1, y);
		} else {
			printf("%d\n", query(x - 1, y - 1));
		}
	}
	return 0;
}
