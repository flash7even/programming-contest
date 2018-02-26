/**
    Suffix array implementation using bucket sorting + lcp.
    Complexity O(n log n), text is the target string.
    1. Fill text with the input string.
    2. Assign len = length of text.
    3. Call suffixSort()
    4. Result is at 2 different arrays: suffix[i] contains index of i'th sorted string
       and sufRank[stp][i] contains rank of i'th suffix.
**/

#define MAXN 500005 /// Maximum string length
#define MAXL 20 /// log(MAXN)

int suffix[MAXN], tmp[MAXN];
int sum[MAXN], cnt[MAXN], sufRank[MAXL][MAXN];
string text;

inline bool sufixCmp(const int &a, const int &b){
    if(text[a] != text[b]) return text[a] < text[b];
    return false;
}

struct suffixArray{
    int len, stp, mv;

    inline bool equal(const int &u, const int &v){
        if(!stp) return text[u] == text[v];
        if(sufRank[stp-1][u] != sufRank[stp-1][v]) return false;
        int a = u + mv < len ? sufRank[stp-1][u+mv] : -1;
        int b = v + mv < len ? sufRank[stp-1][v+mv] : -1;
        return a == b;
    }

    void update(){
        int rnk = 0;
        FOR(i, 0, len-1) sum[i] = 0;
        FOR(i, 0, len-1) {
            suffix[i] = tmp[i];
            if(i && !equal(suffix[i], suffix[i-1])) {
                sufRank[stp][suffix[i]] = ++rnk;
                sum[rnk+1] = sum[rnk];
            }
            else sufRank[stp][suffix[i]] = rnk;
            sum[rnk+1]++;
        }
    }

    void bucketSort() {
        FOR(i, 0, len-1) cnt[i] = 0;
        CLR(tmp, -1);
        FOR(i, 0, mv-1){
            int idx = sufRank[stp - 1][len - i - 1];
            int x = sum[idx];
            tmp[x+cnt[idx]] = len - i - 1;
            cnt[idx]++;
        }
        FOR(i, 0, len-1){
            int idx = suffix[i] - mv;
            if(idx < 0)continue;
            idx = sufRank[stp-1][idx];
            int x = sum[idx];
            tmp[x + cnt[idx]] = suffix[i] - mv;
            cnt[idx]++;
        }
        update();
    }

    void suffixSort() {
        FOR(i, 0, len-1) tmp[i] = i;
        sort(tmp, tmp + len, sufixCmp);
        stp = 0;
        update();
        ++stp;
        for(mv = 1; mv < len; mv <<= 1) {
            bucketSort();
            stp++;
        }
        stp--;
        FOR(i, 0, stp) sufRank[i][len] = -1;
    }

    /// Here u and v are unsorted suffix string position
    inline int lcp(int u, int v) {
        if(u == v) return len - u;
        int ret = 0;
        ROF(i, 0, stp) {
            if(sufRank[i][u] == sufRank[i][v]) {
                ret += 1<<i;
                u += 1<<i;
                v += 1<<i;
            }
        }
        return ret;
    }

}suffixary;
