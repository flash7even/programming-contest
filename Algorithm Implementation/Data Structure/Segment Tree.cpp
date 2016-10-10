#include <bits/stdc++.h>
using namespace std;
#define Size 100005

/**
    Given an array there will be some queries of 2 operations.
    1. Update A[u] to x.
    2. Get maximum element in range u to v.
**/

struct vert{
	int val;
};

int N,Q;
vert T[Size*4];
int A[Size];

/// Both in update & query function:
/// if(M >= v) There is no valid segment in right child, So call for only left child.
/// if(M < u) There is no valid segment in left child, So call for only right child.

void bT(int cur,int s,int e){
    if(s == e){
        T[cur].val = A[s];
        return;
    }
    int L = cur*2,R = cur*2+1,M = (s+e)/2;

    bT(L,s,M);
    bT(R,M+1,e);
    T[cur].val = max(T[L].val,T[R].val);
}

void uT(int cur,int s,int e,int u,int v,int val){
    if(e < u || s > v) return;
    if(s >= u && e <= v){
        T[cur].val = val;
        return;
    }
    int L = cur*2,R = cur*2+1,M = (s+e)/2;

    uT(L,s,M,u,v,val);
    uT(R,M+1,e,u,v,val);
    T[cur].val = max(T[L].val,T[R].val);
}

vert qT(int cur,int s,int e,int u,int v){
    vert vv;
    if(e < u || s > v){
        vv.val = 0;
        return vv;
    }
    if(s >= u && e <= v){
        vv.val = T[cur].val;
        return vv;
    }
    int L = cur*2,R = cur*2+1,M = (s+e)/2;

    vert v1 = qT(L,s,M,u,v);
    vert v2 = qT(R,M+1,e,u,v);
    vv.val = max(v1.val,v2.val);
    return vv;
}

int main() {
    int u,v,val,typ;

	sf("%d",&N);
	for(int i = 1;i<=N;i++){
		sf("%d",&A[i]);
	}
	bT(1,1,N);
	sf("%d",&Q);
	for(int i = 1;i<=Q;i++){
		sf("%d",typ);
		if(typ == 1){  /// Update:
			sf("%d %d",&u,&val);
			uT(1,1,N,u,u,val);
		}else{
			sf("%d %d",&u,&v);  /// Query:
			vert res = qT(1,1,N,u,v);
			pf("%d\n",res.val);
		}
	}
    return 0;
}
