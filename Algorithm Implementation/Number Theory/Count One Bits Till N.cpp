LL countBit(LL num) {
    LL count = 0,one = 1;
    while (num > 0) {
        LL n = 0;
        while (num >= one << (n + one)) {
            n++;
        }
        num -= (one << n);
        count += (num + one + (one << (n - one)) * n);
    }
    return count;
}
