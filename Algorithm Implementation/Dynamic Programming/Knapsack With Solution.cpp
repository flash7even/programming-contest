/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

/// 0/1 Knapsack Problem
/// Maximizing price by not taking more than weight W
/// Tabulation Technique
/// Time Complexity O(N*W)
/// Row of DP table should be N and Column of DP table should b W

#define MAX 1000

int price[MAX];
int weight[MAX];
int DP[MAX][MAX];
vector <int> sol;

int solve(int N, int W) {
	for (int i = 0; i <= N; i++) {
		for (int w = 0; w <= W; w++) {
			if (i == 0 || w == 0) {
				DP[i][w] = 0;
			} else if (weight[i] <= w) {
				DP[i][w] = max(price[i] + DP[i - 1][w - weight[i]],
						       DP[i - 1][w]);
			} else {
				DP[i][w] = DP[i - 1][w];
			}
		}
	}
	return DP[N][W];
}

void solution_print(int i, int k) {
	while (i > 0 && k > 0) {
		if (DP[i][k] != DP[i - 1][k]) {
			sol.push_back(i); /// Mark the item that must take
			k = k - weight[i];
		}
		i = i - 1;
	}
}

int main() {
	int N, W; /// N is the number of items and W is maximum weight
	cin >> N >> W;
	for (int i = 1; i <= N; i++){
		cin >> price[i] >> weight[i];
	}
	cout << solve(N, W) << endl;
	/// Print Solution
	/// Taking which items that makes maximizing price
	solution_print(N, W);
	for (int i = 0; i < (int)sol.size(); i++){
		cout << sol[i] << " ";
	}
	return 0;
}
