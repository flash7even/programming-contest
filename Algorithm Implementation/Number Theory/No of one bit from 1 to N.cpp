#include <bits/stdc++.h>
using namespace std;

long long count_bits(long long num) {
	long long count = 0,one = 1;
	while (num > 0) {
		long long n = 0;
		while (num >= one << (n + one)) {
			n++;
		}
		num -= (one << n);
		count += (num + one + (one << (n - one)) * n);
	}
	return count;
}

int main() {
	long long s, t, ret1, ret2;
	while (scanf("%lld %lld", &s, &t) == 2) {
		ret1 = count_bits(s - 1);
		ret2 = count_bits(t);
		printf("%lld\n", (long long)(ret2 - ret1));
	}
	return 0;
}
