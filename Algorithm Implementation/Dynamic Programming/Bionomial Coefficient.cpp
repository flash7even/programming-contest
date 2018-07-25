int DP[Size][Size];

void binomialCoeff() {
    CLR(DP,0);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= min(i, k); j++) {
            if (j == 0 || j == i) {
                DP[i][j] = 1;
            } else {
                DP[i][j] = DP[i - 1][j - 1] + DP[i - 1][j];
            }
        }
    }
}
