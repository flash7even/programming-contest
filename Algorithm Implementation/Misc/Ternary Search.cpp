/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

LL calcCost(LL mid) {
	/// Calculate cost for mid and return:
}

LL ternarySearch() {
	LL L = 0, R = Max, cnt = 70;
	LL res = Max;

	while (cnt--) {
		/// Both of this approach works.

		//double mid_L = (L + (R - L) / 3);
		//double mid_R = (R - (R - L) / 3);

		double mid_L = (2*L + R) / 3;
		double mid_R = (L + 2*R) / 3;

		if (calcCost(mid_R) < calcCost(mid_L)){
			L = mid_L;
			res = min(res,calcCost(mid_R));
		}else{
			R = mid_R;
		}
	}

	res = min(res,calcCost(L));
	res = min(res,calcCost(R));
	return res;
}
