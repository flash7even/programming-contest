/**
	Suppose you are given a array of N integers. (1<=N,A[i]<=10^5).
	Now you have to find all the GCD of all pairs of numbers you cane
	make from the array.For example if the array is {7,18,20,35} Then
	you can make the pairs (7,18),(7,20),(7,35),(18,20),(18,35)&(20,35).
	Now take the GCD of that pairs 1,1,7,2,1,5.Now you have to print like
	this: (1 = 3),(7 = 1),(2 = 1),(5 = 1).

**/

#include <bits/stdc++.h>
using namespace std;
#define Size 1000005
#define Max 100005

long long GCD(long long A, long long b) {
	if (b == 0) return A;
	return GCD(b, A % b);
}

long long N;
long long A[Size];
long long divs[Size];
long long freq[Size];
long long resGCD[Size]; /// Stores the actual result,resGCD[i] = for how many different pairs i is GCD of them.

void find_GCD_Of_All_Pairs(){
	/// divs[i] = total numbers for which i is a divisor;
	for (int i = 1; i <= A[N]; i++) {
		for (int j = 1; j * i <= A[N]; j++){
			divs[i] += freq[j * i];
		}
	}

	for (int K = A[N]; K >= 1; K--) {
		/// resGCD[K] = How many pairs are there for
		/// which K is a common divisor.The given
		/// formula calculate all possible pairs;
		/// Remember,K is common divisor of all those
		/// pairs but K might not be the GCD of all of them.
		/// So we are over calculating for some pairs;
		resGCD[K] = (divs[K] * (divs[K] - 1)) / 2;

		/// Now we need to remove those pairs who have
		/// a GCD value which is multiple of K
		/// Because there multiple(K*x) values are the GCDs for
		/// those pairs and we have already calculated them
		/// before.So we need to subtract them now.
		/// We are using inclusion exclusion principal here;
		for (int j = 2; K * j <= A[N]; j++) {
			resGCD[K] -= resGCD[K * j];
		}
	}
	for (int i = 1; i <= A[N]; i++){
		if (resGCD[i] != 0) {
			printf("i%d = %lld\n",i,resGCD[i]);
		}
	}
}

int main() {
	cin >> N;
	/// freq[i] = number of occurrences of i in Array;
	for (int i = 1; i <= N; i++) {
		cin >> A[i];
		freq[A[i]]++;
	}
	sort(A + 1, A + N + 1);
	find_GCD_Of_All_Pairs();
	return 0;
}
