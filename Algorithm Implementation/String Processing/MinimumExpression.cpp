///Returns the smallest index which is lexicographically smallest rotation
inline int minimumExpression(char *s) {
    int i, j, k, n, len, p, q;
    len = n = strlen(s), n <<= 1, i = 0, j = 1, k = 0;
    while(i + k < n && j + k < n) {
        p = i+k >= len ? s[i+k-len] : s[i+k];
        q = j+k >= len ? s[j+k-len] : s[j+k];
        if(p == q) k++;
        else if(p > q) { i = i+k+1; if(i <= j) i = j+1; k = 0; }
        else if(p < q) { j = j+k+1; if(j <= i) j = i+1; k = 0; }
    }
    return i < j ? i : j;
}
