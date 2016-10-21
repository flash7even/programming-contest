#include <bits/stdc++.h>
using namespace std;

/**
    Suffix array implementation using bucket sorting + build_LCP_Table.
    Complexity O(N log N), str[] is the target string,
    N is its length and suffix[i] contains i'th sorted suffix position.
**/

const int Max = (1 << 16);

int N, step, mv, suffix[Max], tmp[Max];
int sum[Max], cnt[Max], ranks[16][Max];
int LCP[Max];
char str[Max];

inline bool equal(const int &u, const int &v){
    if(!step) return str[u] == str[v];
    if(ranks[step-1][u] != ranks[step-1][v]) return false;
    int a = u + mv < N ? ranks[step-1][u+mv] : -1;
    int b = v + mv < N ? ranks[step-1][v+mv] : -1;
    return a == b;
}

void update(){
    int i, rnk;
    for(i = 0; i < N; i++) sum[i] = 0;
    for(i = rnk = 0; i < N; i++) {
        suffix[i] = tmp[i];
        if(i && !equal(suffix[i], suffix[i-1])) {
            ranks[step][suffix[i]] = ++rnk;
            sum[rnk+1] = sum[rnk];
        }
        else ranks[step][suffix[i]] = rnk;
        sum[rnk+1]++;
    }
}

void Sort() {
    int i;
    for(i = 0; i < N; i++) cnt[i] = 0;
    memset(tmp, -1, sizeof tmp);
    for(i = 0; i < mv; i++){
        int idx = ranks[step - 1][N - i - 1];
        int x = sum[idx];
        tmp[x + cnt[idx]] = N - i - 1;
        cnt[idx]++;
    }
    for(i = 0; i < N; i++){
        int idx = suffix[i] - mv;
        if(idx < 0)continue;
        idx = ranks[step-1][idx];
        int x = sum[idx];
        tmp[x + cnt[idx]] = suffix[i] - mv;
        cnt[idx]++;
    }
    update();
    return;
}

inline bool cmp(const int &a, const int &b){
    if(str[a]!=str[b]) return str[a]<str[b];
    return false;
}

void build_Suffix_Array() {
    int i;
    for(i = 0; i < N; i++) tmp[i] = i;
    sort(tmp, tmp + N, cmp);
    step = 0;
    update();
    ++step;
    for(mv = 1; mv < N; mv <<= 1) {
        Sort();
        step++;
    }
    step--;
    for(i = 0; i <= step; i++) ranks[i][N] = -1;
}

/// Return longest common prefix of u & v.
int lcpLen(int u, int v) {
    if(u == v) return N - u;
    int ret, i;
    for(ret = 0, i = step; i >= 0; i--) {
        if(ranks[i][u] == ranks[i][v]) {
            ret += 1<<i;
            u += 1<<i;
            v += 1<<i;
        }
    }
    return ret;
}

int main() {
	scanf("%s",&str);
	N = strlen(str);
	build_Suffix_Array();
	return 0;
}
