struct vert{
	int val;
};

int N,Q;
vert T[Size*4];
int A[Size];

/// Both in update & query function:
/// if(M >= v) There is no valid segment in right child, So call for only left child.
/// if(M < u) There is no valid segment in left child, So call for only right child.

void bt(int c,int s,int e){
    if(s == e){
        T[c].val = A[s];
        return;
    }
    int L = c*2,R = c*2+1,M = (s+e)/2;

    bt(L,s,M);
    bt(R,M+1,e);
    T[c].val = T[L].val + T[R].val;
}

void ut(int c,int s,int e,int u,int v,int val){
    if(e < u || s > v) return;
    if(s >= u && e <= v){
        T[c].val = val;
        return;
    }
    int L = c*2,R = c*2+1,M = (s+e)/2;

    ut(L,s,M,u,v,val);
    ut(R,M+1,e,u,v,val);
    T[c].val = T[L].val + T[R].val;
}

int qt(int c,int s,int e,int u,int v){
    if(e < u || s > v) return 0;
    if(s >= u && e <= v) return T[c].val;

    int L = c*2,R = c*2+1,M = (s+e)/2;

    int v1 = qt(L,s,M,u,v);
    int v2 = qt(R,M+1,e,u,v);
    return v1 + v2;
}
