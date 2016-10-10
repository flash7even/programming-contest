#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
#define x first
#define y second

pii extended_euclid(int a, int b) {
	if (b == 0) {
		return pii(1, 0);
	} else {
		pii d = extended_euclid(b, a % b);
		return pii(d.y, d.x - d.y * (a / b));
	}
}

int modular_Inverse(int a, int n) {
	pii ret = extended_euclid(a, n);
	return ((ret.x % n) + n) % n;
}

/// Chinese Remainder Theorem:
/// Returns the smallest
/// number x such that:
///  x % mod[0] = rem[0],
///  x % mod[1] = rem[1],
///  ..................
///  x % mod[k-1] = rem[k-1]
///  Numbers in mod[] are pairwise co prime.

/// x = MOD[1]*Inv[1]*rem[1] + MOD[2]*Inv[2]*rem[2] + . . . + MOD[k]*Inv[k]*rem[k];
/// MOD[i] = (mod[1]*mod[2]*....*mod[k])/(mod[i]);
/// Find Inv[i] such that, MOD[i]*Inv[i] == 1(% mod[i]) (using modulo inverse);

int k; /// k is the size.
int mod[105];
int rem[105];

int CRT(){
    int prod = 1;
    for (int i = 0; i < k; i++){
        prod *= mod[i];
    }
    int result = 0;
    for (int i = 0; i < k; i++){
        int pp = prod / mod[i];
        result += rem[i] * modular_Inverse(pp, mod[i]) * pp;
    }
    return (result % prod);
}

int main(void){
    cin >> k;
    for(int i = 0;i<k;i++) cin >> mod[i];
    for(int i = 0;i<k;i++) cin >> rem[i];
    int x = CRT();
    printf("The x is : %d\n",x);
    return 0;
}
