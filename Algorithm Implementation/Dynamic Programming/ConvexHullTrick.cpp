/**
Instructions
-> For Linear Version:
1. Sort lines based on decreasing M and in case of tie, increasing B.
2. Sort query points according to increasing X.
3. Clear the class, add all lines and then query.

-> For Dynamic Version:
1. Just insert lines in any order
2. Query points in any order
3. Query at any time, even in between updates
**/

vlong n, k, dp[Size], tmp[Size];
vlong cost[Size], val[Size], sum[Size];

inline vlong getConst(vlong u) {
    return dp[u] + u * sum[u] - cost[u];
    // constant part: *** EDIT HERE ***
}

/// dp when last partition ended at u and this one ends at v
inline vlong getDP(vlong u, vlong v) {
    return cost[v] - v * sum[u] + getConst(u);
    // partition equation: *** EDIT HERE ***
}

// derived from equation above
// m = -sum[u]
// c = getconst(u)
// have to minimize m*sum[v] + c
// have to maximize -m*sum[v] - c

/**
Convex Hull Linear
needs increasing x/decreasing slopes
Minimizes Result: mx + b
Insert lines with slope = m, const = b
Query best result for x with eval(x)
Complexity: N [ for infinite partition ], NK [ for K partition ]
**/

class HullLinear {

    int pointer; //Keeps track of the best line from previous query
    vector<long long> M; //Holds the slopes of the lines in the envelope
    vector<long long> B; //Holds the y-intercepts of the lines in the envelope

    //Returns true if line l3 is always better than line l2
    bool bad(int l1,int l2,int l3){
        /*
        intersection(l1,l2) has x-coordinate (b1-b2)/(m2-m1)
        intersection(l1,l3) has x-coordinate (b1-b3)/(m3-m1)
        set the former greater than the latter, and cross-multiply to
        eliminate division. use deterministic comuputation with long
        long if sufficient.
        */
        return (B[l3]-B[l1])*(M[l1]-M[l2])<(B[l2]-B[l1])*(M[l1]-M[l3]);
    }

    public:

    void clear() {
        pointer = 0;
        M.clear();
        B.clear();
    }

    //Adds a new line (with lowest slope) to the structure
    void insert_line(long long m,long long b){
        if ( M.size() > 0 && M.back() == m ) return; ///Same Gradient. Don't add.

        //First, let's add it to the end
        M.push_back(m);
        B.push_back(b);
        //If the penultimate is now made irrelevant between the antepenultimate
        //and the ultimate, remove it. Repeat as many times as necessary
        while (M.size()>=3&&bad(M.size()-3,M.size()-2,M.size()-1)){
            M.erase(M.end()-2);
            B.erase(B.end()-2);
        }
    }

    //Returns the minimum y-coordinate of any intersection between a given vertical
    //line and the lower envelope
    long long eval(long long x){
        //Any better line must be to the right, since query values are
        //non-decreasing
        while (pointer<M.size()-1 &&
            M[pointer+1]*x+B[pointer+1]<M[pointer]*x+B[pointer]) {
                pointer++;
        }
        return M[pointer]*x+B[pointer];
    }

} hull;

/**
Dynamic Convex Hull
Does not need increasing x/decreasing slopes
Maximizes Result: mx + b
Insert lines with slope = m, const = b
Query best result for x with eval(x)
Complexity: NlogN [ for infinite partition ], NKlogN [ for K partition ]
**/

const vlong is_query = -(1LL<<62);

struct Line {
    vlong m, b;
    mutable function<const Line*()> succ;
    bool operator<(const Line& rhs) const {
        if (rhs.b != is_query) return m < rhs.m;
        const Line* s = succ();
        if (!s) return 0;
        vlong x = rhs.m;
        return (long double)(b - s->b) < (long double)(s->m - m) * x;
    }
};

struct HullDynamic : public multiset<Line> { // will maintain upper hull for maximum

    bool bad(iterator y) {
        auto z = next(y);
        if (y == begin()) {
            if (z == end()) return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end()) return y->m == x->m && y->b <= x->b;
        return (long double)(x->b - y->b)*(z->m - y->m) >= (long double)(y->b - z->b)*(y->m - x->m);
    }

    void insert_line(vlong m, vlong b) {
        auto y = insert({ m, b });
        y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y)) { erase(y); return; }
        while (next(y) != end() && bad(next(y))) erase(next(y));
        while (y != begin() && bad(prev(y))) erase(prev(y));
    }

    vlong eval(vlong x) {
        auto l = lower_bound((Line) { x, is_query });
        //if (l == end()) return 0;
        return l->m * x + l->b;
    }

} hull;
