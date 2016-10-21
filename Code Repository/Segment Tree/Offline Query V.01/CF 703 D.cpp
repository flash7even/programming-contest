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

#define Size 1000005

/// Problem Link : http://codeforces.com/contest/703/problem/D
/// We'll iterate for all end index from 1 to N.
/// Then for each end position we'll handle all the queries whose end index is
/// smaller equal this index.
/// Complexity : Q*log(N)

struct qry{
    int u;
    int v;
    int idx;
    qry(){
    }
    qry(int a,int b,int c){
        u = a;
        v = b;
        idx = c;
    }
};

bool cmp(qry a,qry b){
    if(a.v == b.v) return (a.u<b.u);
    return (a.v<b.v);
}

int N,QQ;
int A[Size];
qry Q[Size];
int res[Size];
int T[4*Size];
int cxor[Size];
map<int,int> Map;

void ut(int cur,int st,int ed,int u,int v,int val){
    if(st>v || ed<u) return;
    if(st>=u && ed<=v){
        T[cur] = val;
        return;
    }
    int L = cur*2, R = cur*2+1, M = (st+ed)/2;

    ut(L,st,M,u,v,val);
    ut(R,M+1,ed,u,v,val);
    T[cur] = T[L]^T[R];
}

int qt(int cur,int st,int ed,int u,int v){
    if(st>v || ed<u) return 0;
    if(st>=u && ed<=v){
        return T[cur];
    }
    int L = cur*2, R = cur*2+1, M = (st+ed)/2;

    int a = qt(L,st,M,u,v);
    int b = qt(R,M+1,ed,u,v);
    return a^b;
}

void solve(){
    int cq = 0;
    /// We'll try to handle all the queries together whose end position is ed.
    /// Map[x] = Position of the last occurrence of x till now.
    for(int ed = 1;ed<=N;ed++){
        if(Map.count(A[ed]) != 0){ /// We have already updated for this value before.
            int ps = Map[A[ed]];
            ut(1,1,N,ps,ps,0); /// Remove the previous occurrence of A[ed].
        }
        ut(1,1,N,ed,ed,A[ed]); /// Update the current occurrence.
        Map[A[ed]] = ed;
        while(Q[cq].v == ed){
            if(cq >= QQ) break;
            /// xrRng = xor value of odd times occurred elements in the range.
            /// Because xor of even times occurred elements is zero.
            int xrRng = cxor[Q[cq].v] ^ cxor[Q[cq].u-1];
            /// xor value of all the unique element in the range.
            int xrUnq = qt(1,1,N,Q[cq].u,Q[cq].v);
            res[Q[cq].idx] = xrRng ^ xrUnq;
            cq++;
        }
    }
}

int main(){
	sf("%d",&N);
	cxor[0] = 0;
	for(int i = 1;i<=N;i++){
        sf("%d",&A[i]);
        cxor[i] = cxor[i-1]^A[i];
	}
    sf("%d",&QQ);
	for(int i = 0;i<QQ;i++){
        sf("%d %d",&Q[i].u,&Q[i].v);
        Q[i].idx = i;
	}
	/// Sort according to increasing value of v.
    sort(Q,Q+QQ,cmp);
    solve();
    for(int i = 0;i<QQ;i++){
        pf("%d\n",res[i]);
    }
	return 0;
}
