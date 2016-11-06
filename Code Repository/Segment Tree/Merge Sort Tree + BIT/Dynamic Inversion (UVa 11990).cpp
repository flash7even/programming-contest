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
#define NORM(x) if(x>=mod) x-=mod;if(x<0) x+=mod;
#define MOD(x,y) (((x)*(y))%mod)
#define ODD(x) (((x)&1)==0?(0):(1))
#define Set(N,cur) N=(N|(1LL<<cur))
#define Reset(N,cur) N=(N&(~(1LL<<cur)))
#define Check(N,cur) (!((N&(1LL<<cur))==0))
#define fast_cin ios_base::sync_with_stdio(false);cin.tie(NULL)

using namespace std;


#define LL long long
#define LLU long long unsigned int
typedef long long vlong;
typedef unsigned long long uvlong;
typedef pair < int, int > pii;
typedef pair < vlong, vlong > pll;
typedef vector<int> vi;
typedef vector<vlong> vl;
typedef vector<pll> vll;

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


//int knightDir[8][2] = { {-2,1},{-1,2},{1,2},{2,1},{2,-1},{-1,-2},{1,-2},{-2,-1} };
//int dir4[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
//int dir8[8][2] = {{-1,0},{0,1},{1,0},{0,-1},{-1,-1},{1,1},{1,-1},{-1,1}};
const vlong inf = 2147383647;
const vlong mod = 1000000007;
const double pi = 2 * acos ( 0.0 );
const double eps = 1e-9;

///======================  TEMPLATE ENDS HERE  =====================///

#define Size 200005

/// Problem Link : http://vjudge.net/problem/UVA-11990

/***
    IDEA:
    01. In each node we'll built a vector augmented segment tree
    02. Each T[i] will save all the elements in it's subtree in ascending order
    03. Each bit[i] represents a binary index tree for a segment tree node T[i] considering the number of elements in it.
    04. It's a position based bit which we generally do for finding inversions.
    05. Initially all the positions in all the bit[i] is set on as all the elements exist.

    06. Let's say we want to remove num from the segment tree.
    07. Let's cur be a segment tree node which contains num.
    08. First of all we'll have to find the position of num in T[cur] using binary search, let's say that position is pos.
    09. Now remove it(update by adding -1) from bit[cur]

    10. Let's say we want to find number of elements smaller than num from the segment tree(in a range).
    11. Let's cur be a segment tree node which contains the valid range.
    12. Again we'll have to find the position of num in T[cur] using binary search,let's say that position is pos.
    13. We'll have to find no of positions from 1 to pos is set on in bit[cur]
    14. That's our result.

    Solution Credit : Jubayer Rahman Nirjhor(IOI)
***/

vector<int> T[Size*4],bit[Size*4],ibit;
int A[Size],P[Size],B[Size];

void update (vector<int> &bit, int u, int v, int MAX) {
    while (u <= MAX){
        bit[u] += v;
        u += (u & -u);
    }
}

int query (vector<int> &bit, int u) {
    int sum = 0;
    while (u > 0){
        sum += bit[u];
        u -= (u & -u);
    }
    return sum;
}

void bt(int cur,int s,int e){
    if(s == e){
        T[cur].clear();
        T[cur].pb(A[s]);
        bit[cur].resize(1+1,0);
        update(bit[cur],1,1,1);
        return;
    }
    int L = cur*2,R = cur*2+1,M = (s+e)/2;
    bt(L,s,M);
    bt(R,M+1,e);

    int szz = SZ(T[L]) + SZ(T[R]);
    T[cur].clear();
    T[cur].resize(szz);
    bit[cur].resize(szz+1,0);
    merge(ALL(T[L]),ALL(T[R]),T[cur].begin()); /// merge T[L] & T[R] in T[cur] (ascending order)
    for(int i = 1;i<=szz;i++){
        update(bit[cur],i,1,szz); /// Initially all the numbers exist, so set all the positions in bit[i] to on
    }
}

void ut(int cur,int s,int e,int u,int v,int val){
    if(e < u || s > v) return;
    /// This node contain val.
    /// Find val's position in T[cur] and remove it from bit[cur]
    if(s >= u && e <= v){
    	int pos = lower_bound(ALL(T[cur]), val) - T[cur].begin() + 1;
    	update(bit[cur],pos,-1,SZ(T[cur]));
    	return;
    }
    int L = cur*2,R = cur*2+1,M = (s+e)/2;
    int pos = lower_bound(ALL(T[cur]), val) - T[cur].begin() + 1;
    update(bit[cur],pos,-1,SZ(T[cur]));
    ut(L,s,M,u,v,val);
    ut(R,M+1,e,u,v,val);
}

LL qt(int cur,int s,int e,int u,int v,int val,int f){
    if(e < u || s > v) return 0;
    if(s >= u && e <= v){
        int pos = upper_bound(ALL(T[cur]), val) - T[cur].begin();
        /// All the elements from 0 to pos is smaller than val.
        /// So to find no of elements smaller than val which exist in this range
        /// we have to find no of positions from 0 to pos is set on in bit[cur]
        int s1 = query(bit[cur],pos);
        if(f == 1) return s1; /// No of elements smaller than val
        int s2 = query(bit[cur], SZ(T[cur]));
        return s2 - s1; /// No of elements greater than val
    }
    int L = cur*2,R = cur*2+1,M = (s+e)/2;

    LL v1 = qt(L,s,M,u,v,val,f);
    LL v2 = qt(R,M+1,e,u,v,val,f);
    return v1 + v2;
}

int main() {
    #ifdef forthright48
    freopen ( "Ainput.txt", "r", stdin );
    //freopen ( "output.txt", "w", stdout );
    #endif // forthright48

    int N,Q,num;
	while(scanf("%d %d",&N,&Q) == 2){
        for(int i = 0;i<=N*4;i++){
            bit[i].clear();
            T[i].clear();
        }
        ibit.clear();
        ibit.resize(Size,0);
        for(int i = 1;i<=N;i++){
            scanf("%d",&A[i]);
            P[A[i]] = i;
            B[i] = A[i];
        }
        /// Initial inversions considering all elements
        LL inversions = 0;
        sort(B+1,B+N+1);
        for(int i = 1;i<=N;i++){
            inversions += (query(ibit, N) - query(ibit, P[B[i]]));
            update(ibit, P[B[i]], 1, Size);
        }
        bt(1,1,N);
        while(Q--){
            printf("%lld\n",inversions);
            scanf("%d",&num);
            int pos = P[num];
            int s1 = qt(1,1,N,1,pos-1,num,2); /// No of elements greater than num in range 1 to pos-1
            int s2 = qt(1,1,N,pos+1,N,num,1); /// No of elements smaller than num in range pos+1 to N
            inversions -= (s1+s2);
            ut(1,1,N,pos,pos,num); /// Remove num from the segment tree & bit
        }
	}
    return 0;
}
