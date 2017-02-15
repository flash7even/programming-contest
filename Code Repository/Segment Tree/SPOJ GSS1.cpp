#include <bits/stdc++.h>
using namespace std;
#define Size 50005

int N, Q;
int A[Size];

struct vert {
	int tot;
	int Mx;
	int mxSfx;
	int mxPfx;
	vert() {
		tot = Mx = mxSfx = mxPfx = 0;
	}
};

vert T[Size * 4];

vert merge(vert L,vert R){
    vert c;
	c.tot = L.tot + R.tot;
	c.Mx = max(L.Mx, R.Mx);
	c.Mx = max(c.Mx, c.tot);
	c.Mx = max(c.Mx, L.mxSfx + R.mxPfx);
	c.mxPfx = max(L.mxPfx, L.tot + R.mxPfx);
	c.mxSfx = max(R.mxSfx, R.tot + L.mxSfx);
	return c;
}

void bt(int c, int s, int e) {
	if (s == e) {
		T[c].tot = T[c].Mx = A[s];
		T[c].mxSfx = T[c].mxPfx = A[s];
		return;
	}
	int L = c * 2,R = c * 2 + 1,M = (s + e) / 2;

	bt(L, s, M);
	bt(R, M + 1, e);

	T[c] = merge(T[L],T[R]);
}

vert qt(int c, int s, int e, int u, int v) {
	if (e < u || s > v) return vert();

	if (s >= u && e <= v) {
		return T[c];
	}
	int L = c * 2,R = c * 2 + 1,M = (s + e) / 2;

	vert v1 = qt(L, s, M, u, v);
	vert v2 = qt(R, M + 1, e, u, v);

	if (M>=v)  return v1;
	else if (M<u) return v2;
	else return merge(v1,v2);
}

int main() {
	int u, v;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++){
		scanf("%d", &A[i]);
	}
	memset(T, -1, sizeof(T));
	scanf("%d", &Q);
	bt(1, 1, N);
	for (int i = 0; i < Q; i++) {
		scanf("%d %d", &u, &v);
		vert rs = qt(1, 1, N, u, v);
		printf("%d\n", rs.Mx);
	}
	return 0;
}
