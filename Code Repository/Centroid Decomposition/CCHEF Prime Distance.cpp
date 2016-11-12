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

/// Problem Link : https://www.codechef.com/problems/PRIMEDST
/// Idea Link : https://threads-iiith.quora.com/Centroid-Decomposition-of-a-Tree

const int N = 50005;
LL ans,szz,len;
const int LOGN = 17;
set<int> Graph[N];
int ndist[LOGN][N],sz[N];
int Prime[N],mark[N];

void getSize(int u,int p){
	sz[u] = 1;
	szz++;
	for(auto it = Graph[u].begin();it!=Graph[u].end();it++){
		int v = *it;
		if(v != p){
			getSize(*it,u),sz[u] += sz[v];
		}
	}
}

int getCenter(int u,int p) {
	for(auto it = Graph[u].begin();it!=Graph[u].end();it++){
		int v = *it;
		if(v != p && sz[v]>szz/2){
			return getCenter(*it,u);
		}
	}
	return u;
}


/// Update the ndist array by add in a subtree:

void updateSubtree(int u,int p,int level,int dist,int add){
	ndist[level][dist] += add;
	for(auto it = Graph[u].begin();it != Graph[u].end();it++){
		int v = *it;
		if(v != p){
			updateSubtree(v,u,level,dist+1,add);
		}
	}
}

LL findRes(int u,int p,int level,int dist){
	LL ret = 0;

	for(int i = 0;i<len;i++){ /// Loop for all the primes
		if(Prime[i] - dist<0) continue;
		if(ndist[level][Prime[i] - dist] == 0) break;

		if(Prime[i] != dist){ /// Not root
			ret += ndist[level][Prime[i]-dist];
			/// We don't need to multiply by 2
			/// Because eventually this path will be counted twice
		}else{
			ret += 2*ndist[level][Prime[i]-dist];
			/// Path from current node to the root
			/// Multiply by 2 so that this path is counted twice
		}
	}

	for(auto it = Graph[u].begin();it != Graph[u].end();it++){
		int v = *it;
		if(v != p){
			ret += findRes(v,u,level,dist+1);
		}
	}
	return ret;
}

void decompose(int root,int level){
	szz = 0;

	getSize(root,root);
	int centroid = getCenter(root,root);

	updateSubtree(centroid,centroid,level,0,1); /// Initially add all the subtree of root:
	LL add = 0;
	int u = centroid;

	for(auto it = Graph[u].begin();it != Graph[u].end();it++){
		int v = *it;
		updateSubtree(v,u,level,1,-1); /// Remove current subtree
		add +=  findRes(v,u,level,1);
		updateSubtree(v,u,level,1,1); /// Add current subtree again
	}

	ans += add/2; /// Each pair was counted twice

	for(auto it = Graph[u].begin();it != Graph[u].end();it++){
		int v = *it;
		Graph[v].erase(u); /// Remove all edges of this centroid
		decompose(v,level+1);
	}

	for(int i = 0;i<N && ndist[level][i];i++){
		ndist[level][i] = 0;
	}
}

void seive(){
	for(int i = 2;i*i<N;i++){
		if(!mark[i]){
			for(int j = i*i;j<N;j += i) mark[j] = 1;
		}
	}
	for(int i = 2;i<N;i++){
		if(!mark[i]) Prime[len++] = i;
	}
}

int main(){
	seive();
	int n,a,b;
	scanf("%d",&n);
	for(int i = 0;i<n-1;i++){
		scanf("%d %d",&a,&b);
		a--;b--;
		Graph[a].insert(b);
		Graph[b].insert(a);
	}
	decompose(0,0);
	double dwn = (LL)n*(LL)(n-1)/2.0;
	printf("%0.10lf\n",ans/dwn);
	return 0;
}
