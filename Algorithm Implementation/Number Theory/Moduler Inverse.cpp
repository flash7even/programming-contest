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
