#include <bits/stdc++.h>
using namespace std;
#define Size 1005
#define MAXN 100002

//Time Cmpxty O(n*k) , Space Cmpxty O(n*k)
int binomialCoeff_1(int n, int k) {
	int DP[n + 1][k + 1];
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= min(i, k); j++) {
			if (j == 0 || j == i) {
				DP[i][j] = 1;
			} else {
				DP[i][j] = DP[i - 1][j - 1] + DP[i - 1][j];
			}
		}
	}
	return DP[n][k];
}

//Time Cmpxty O(n*k) , Space Cmpxty O(n)
int binomialCoeff_2(int n, int k) {
	int DP[k+1];
	DP[0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = min(i, k); j > 0; j--){
			DP[j] = DP[j] + DP[j - 1];
		}
	}
	return DP[k];
}

int main() {
	int n = 5, k = 2;
	printf("Value of DP(%d, %d) is %d ", n, k, binomialCoeff_1(n, k));
	return 0;
}
