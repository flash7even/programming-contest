/// Given a group of n men arranged in a circle under the edict that every k'th man
/// will be executed going around the circle until only one remains.
/// Find out who will be the final survivor.

int josephus(int n, int k){
    if (n == 1) return 1;
    return (josephus(n - 1, k) + k-1) % n + 1;
}

/// log base solution when k is 2
int josephus(int n){
    int p = 1;
    while (p <= n) p *= 2;
    return (2*n) - p + 1;
}
