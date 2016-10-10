#include <bits/stdc++.h>
using namespace std;
typedef pair<LL, LL> pii;
#define x first
#define y second

pii extended_euclid(LL a, LL b) {
	if (b == 0) {
		return pii(1, 0);
	} else {
		pii d = extended_euclid(b, a % b);
		return pii(d.y, d.x - d.y * (a / b));
	}
}

LL modular_Inverse(LL a, LL n) {
	pii ret = extended_euclid(a, n);
	return ((ret.x % n) + n) % n;
}

int main() {
	// Extended Euclid Algorithm:
	int A, B, X, Y, n;
	scanf("%d %d %d", &A, &B, &n);
	pii xy = extended_euclid(A, B);
	int mod_inv = modular_Inverse(A, n);
	printf("X: %d , Y: %d\n", xy.x, xy.y);
	printf("Moduler Inverse of: %d for mod: %d = %d\n", A, n, mod_inv);
}
