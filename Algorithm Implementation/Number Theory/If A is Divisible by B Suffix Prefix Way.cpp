#include <bits/stdc++.h>
using namespace std;

string s, t1, t2;
int a, b, N;

long long prefix_mod[1000005];
long long suffix_mod[1000005];

long long big_mod(long long N, long long P, long long Mod) {
	if (P == 0) {
		return 1;
	}
	if (P % 2 == 0) {
		long long ret = big_mod(N, P / 2, Mod);
		return ((ret % Mod) * (ret % Mod)) % Mod;
	} else {
		return ((N % Mod) * (big_mod(N, P - 1, Mod) % Mod)) % Mod;
	}
}

void calc_prefix_mod(string s, long long divisor) {
	long long mod = 0, val = 0;
	int N = s.length();
	for (int i = 0; i < N; i++) {
		val = (long long) (s[i] - '0');
		mod = (mod * 10 + val) % divisor;
		prefix_mod[i] = mod;
	}
}

void calc_suffix_mod(string s, long long divisor) {
	long long mod = 0, val = 0, power = 1;
	int N = s.length();
	int prev_digit = 0;
	for (int i = N - 1; i >= 0; i--) {
		val = (long long) (s[i] - '0');
		mod = ((val * power) % divisor + mod) % divisor;
		suffix_mod[i] = mod;
		prev_digit++;
		power = (power * 10) % divisor;
	}
}

int main() {
	cin >> s >> a >> b;
	N = s.length();
	calc_prefix_mod(s, a);
	calc_suffix_mod(s, b);
	bool res = false;
	for (int i = 0; i < N - 1; i++) {
		if (s[i + 1] == '0')
			continue;
		if (prefix_mod[i] == 0 && suffix_mod[i + 1] == 0) {
			res = true;
			t1 = t2 = s;
			t1 = t1.substr(0, i + 1);
			t2 = t2.substr(i + 1, N);
			break;
		}
	}
	if (res == true) {
		cout << "YES\n" << t1 << endl << t2 << endl;
	} else {
		cout << "NO\n";
	}
}
