#include <bits/stdc++.h>
using namespace std;

string s, t1, t2;
int a, b, N;

long long prefix_mod[1000005];
long long suffix_mod[1000005];

/// Check if s is divisible by div traversing from 0 to len(s):
void calc_prefix_mod(string s, long long div) {
	long long mod = 0, val = 0;
	int N = s.length();
	for (int i = 0; i < N; i++) {
		val = (long long) (s[i] - '0');
		mod = (mod * 10 + val) % div;
		prefix_mod[i] = mod;
	}
}

/// Check if s is divisible by div traversing from len(s) to 0:
void calc_suffix_mod(string s, long long div) {
	long long mod = 0, val = 0, power = 1;
	int N = s.length();
	int prev_digit = 0;
	for (int i = N - 1; i >= 0; i--) {
		val = (long long) (s[i] - '0');
		mod = ((val * power) % div + mod) % div;
		suffix_mod[i] = mod;
		prev_digit++;
		power = (power * 10) % div;
	}
}

int main() {
	cin >> s >> a >> b;
	N = s.length();
	calc_prefix_mod(s, a);
	calc_suffix_mod(s, b);
}
