///==================================================================//
/// Problem     : Contest Code                                       //
/// Author      : NSU Aristocrats                                    //
/// Represents  : North South University                             //
/// Email       : nsu3aristocrats@gmail.com                          //
/// Codeforces  : http://codeforces.com/team/21235                   //
/// Verdict     : In Queue                                           //
/// Date        : 02/10/2016                                         //
///==================================================================//

///====================== TEMPLATE STARTS HERE =====================///
//#include <bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<vector>
#include<deque>
#include<functional>
#include<string>
#include<iostream>
#include<cctype>
#include<set>
#include<climits>
#include<iomanip>
#include<cassert>
#include<sstream>

#define pb push_back
#define nl puts ("")
#define sp printf ( " " )
#define phl printf ( "hello\n" )
#define ff first
#define ss second
#define POPCOUNT __builtin_popcountll
#define RIGHTMOST __builtin_ctzll
#define LEFTMOST(x) (63-__builtin_clzll((x)))
#define MP make_pair
#define FOR(i,x,y) for(vlong i = (x) ; i <= (y) ; ++i)
#define ROF(i,x,y) for(vlong i = (y) ; i >= (x) ; --i)
#define CLR(x,y) memset(x,y,sizeof(x))
#define UNIQUE(V) (V).erase(unique((V).begin(),(V).end()),(V).end())
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define NUMDIGIT(x,y) (((vlong)(log10((x))/log10((y))))+1)
#define SQ(x) ((x)*(x))
#define ABS(x) ((x)<0?-(x):(x))
#define FABS(x) ((x)+eps<0?-(x):(x))
#define ALL(x) (x).begin(),(x).end()
#define LCM(x,y) (((x)/gcd((x),(y)))*(y))
#define SZ(x) ((vlong)(x).size())
#define NORM(x) if(x>=mod)x-=mod;
#define MOD(x,y) (((x)*(y))%mod)
#define ODD(x) (((x)&1)==0?(0):(1))
#define dbgA(A,i) debug("[",i,"] = ",A[i])
#define pf printf
#define sf scanf
#define LL long long
#define LLU long long unsigned int
#define fast_cin ios_base::sync_with_stdio(false);cin.tie(NULL)
#define pline pf("\n\n/// ================================ ///\n\n")

using namespace std;

typedef long long vlong;
typedef unsigned long long uvlong;
typedef pair < vlong, vlong > pll;
typedef pair < int, int > pii;
typedef vector<pll> vll;
typedef vector<vlong> vl;

#ifdef forthright48
     #include <ctime>
     clock_t tStart = clock();
     #define debug(args...) {dbg,args; cerr<<endl;}
     #define timeStamp debug ("Execution Time: ", (double)(clock() - tStart)/CLOCKS_PER_SEC)
     #define bug printf("%d\n",__LINE__);

#else
    #define debug(args...)  // Just strip off all debug tokens
    #define timeStamp
#endif

struct debugger{
    template<typename T> debugger& operator , (const T& v){
        cerr<<v<<" ";
        return *this;
    }
}dbg;

//int knightDir[8][2] = { {-2,1},{-1,2},{1,2},{2,1},{2,-1},{-1,-2},{1,-2},{-2,-1} };
//int dir4[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
//int dir8[8][2] = {{-1,0},{0,1},{1,0},{0,-1},{-1,-1},{1,1},{1,-1},{-1,1}};

inline vlong gcd ( vlong a, vlong b ) {
    a = ABS ( a ); b = ABS ( b );
    while ( b ) { a = a % b; swap ( a, b ); } return a;
}

vlong ext_gcd ( vlong A, vlong B, vlong *X, vlong *Y ){
    vlong x2, y2, x1, y1, x, y, r2, r1, q, r;
    x2 = 1; y2 = 0;
    x1 = 0; y1 = 1;
    for (r2 = A, r1 = B; r1 != 0; r2 = r1, r1 = r, x2 = x1, y2 = y1, x1 = x, y1 = y ) {
        q = r2 / r1;
        r = r2 % r1;
        x = x2 - (q * x1);
        y = y2 - (q * y1);
    }
    *X = x2; *Y = y2;
    return r2;
}

inline vlong modInv ( vlong a, vlong m ) {
    vlong x, y;
    ext_gcd( a, m, &x, &y );
    x %= m;
    if ( x < 0 ) x += m;
    return x;
}

inline vlong power ( vlong a, vlong p ) {
    vlong res = 1, x = a;
    while ( p ) {
        if ( p & 1 ) res = ( res * x );
        x = ( x * x ); p >>= 1;
    }
    return res;
}

inline vlong bigmod ( vlong a, vlong p, vlong m ) {
    vlong res = 1 % m, x = a % m;
    while ( p ) {
        if ( p & 1 ) res = ( res * x ) % m;
        x = ( x * x ) % m; p >>= 1;
    }
    return res;
}

int  Set(int N,int cur){ return N = N | (1<<cur); }
int  Reset(int N,int cur){ return N = N & ~(1<<cur); }
bool Check(int N,int cur){ return (bool)(N & (1<<cur)); }

const vlong inf = 2147383647;
const double pi = 2 * acos ( 0.0 );
const double eps = 1e-9;

///======================  TEMPLATE ENDS HERE  =====================///

const int MAX = 100005;
const int INF = 0x7f7f7f7f;

/// Problem Link : http://www.spoj.com/problems/GSS2/
/// Idea Link : https://www.quora.com/How-can-the-SPOJ-problem-GSS2-be-solved

struct vert{
    LL best;
    /// The best sub array sum which gives maximum result.
    LL slice;
    /// slice is the summation of a sub array such that (slice segment + lazy segment) ends at ed (Check solve function).
    /// Of course, lazy segment starts immediately after slice segments end.
    /// If there's no lazy segment then slice segment ends at ed.
    LL lazy;
    /// summation of all the lazy values till now.
    /// Actually it's like a sub array segment until it is being passed to the child nodes.
    LL bstLazy;
    /// the best prefix of the lazy segment which gives the maximum sum.
};

int N,M;
int A[MAX];
vert T[1<<18];

void updateChilds(vert &cur,vert &L,vert &R){
    /// Note: Lazy segment of cur starts after the lazy segment of R.
    /// lazy segment of R is also included in the lazy segment of L.
    L.bstLazy = MAX(L.bstLazy, L.lazy + cur.bstLazy);
    L.lazy += cur.lazy;

    R.bstLazy = MAX(R.bstLazy, R.lazy + cur.bstLazy);
    R.lazy += cur.lazy;

    cur.lazy = 0;
    cur.bstLazy = 0;
}

void mergeChild(vert &cur,vert &L,vert &R){
    cur.best = MAX(MAX(L.best,L.slice + L.bstLazy), MAX(R.best,R.slice + R.bstLazy));
    cur.slice = MAX(L.slice + L.lazy, R.slice + R.lazy);
    /// Now slice is a whole segment that ends at right most node in R.
    /// But the starting index may be anywhere before end index :P
}

/// Note: while updating we just update the lazy values.
/// We don't update the result for current segment now.

void uT(int cur,int s,int e,int u,int v,int val){
    if(e < u || s > v) return;
    if(s >= u && e <= v){
        T[cur].lazy += val;
        T[cur].bstLazy = MAX(T[cur].lazy, T[cur].bstLazy); /// Best prefix of lazy
        return;
    }
    int L = cur*2,R = cur*2+1,M = (s+e)/2;

    updateChilds(T[cur],T[L],T[R]);

    uT(L,s,M,u,v,val);
    uT(R,M+1,e,u,v,val);
    mergeChild(T[cur],T[L],T[R]);
}

LL qT(int cur,int s,int e,int u,int v){
    if(e < u || s > v) return 0;
    if(s >= u && e <= v){
        return MAX(T[cur].best, T[cur].slice + T[cur].bstLazy); /// Considering lazy part
    }
    int L = cur*2,R = cur*2+1,M = (s+e)/2;

    updateChilds(T[cur],T[L],T[R]);
    mergeChild(T[cur],T[L],T[R]);

    LL v1 = qT(L,s,M,u,v);
    LL v2 = qT(R,M+1,e,u,v);
    return MAX(v1,v2);
}

struct qry{
    int u,v,idx;
};

bool cmp(qry a,qry b){
    if(a.v == b.v) return a.u<b.u;
    return a.v < b.v;
}

qry Q[MAX];
LL res[MAX];
int lstOcr[MAX*2];
/// lstOcr[u] = last occurring position of u.

void solve(){
    sort(Q,Q+M,cmp);
    int cq = 0;
    for(int ed = 1;ed<=N;ed++){
        int val = A[ed]+100000; /// Handle negative value.
        uT(1, 1, N, lstOcr[val] + 1, ed, A[ed]);
        /// A[ed] only affects the suffix that starts after lstOcr[A[ed]];
        lstOcr[val] = ed;
        /// We'll process all the queries together whose v = ed.
        while(Q[cq].v == ed){
            if(cq>=M) break;
            res[Q[cq].idx] = qT(1, 1, N, Q[cq].u, Q[cq].v);
            cq++;
        }
    }
}

int main(){
    #ifdef forthright48
    //freopen ( "Ainput.txt", "r", stdin );
    //freopen ( "output.txt", "w", stdout );
    #endif // forthright48

    sf("%d",&N);
    FOR(i,1,N){
        sf("%d", &A[i]);
    }
    sf("%d",&M);
    FOR(i,0,M-1){
        sf("%d %d",&Q[i].u,&Q[i].v);
        Q[i].idx = i;
    }
    solve();
    FOR(i,0,M-1){
        pf("%lld\n", res[i]);
    }
    return 0;
}
