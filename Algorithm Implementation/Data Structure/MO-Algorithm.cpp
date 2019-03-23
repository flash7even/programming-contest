/// MO's Algorithm
/// Take all the query in qList array and sort them
/// Call MO to solve
/// res[i] contains the result of i'th query
/// Update add and remv function accordingly

const int blockSize = 555;

struct qry {
    int l, r, id;
};

int ans, Q;
/// ans = answer for current range, Q = number of query
int res[Size]; /// res[x] = the answer of x'th query
qry qList[200000 + 10];

bool cmp(qry a, qry b) {
    if (a.l / blockSize == b.l / blockSize) return a.r < b.r;
    return a.l / blockSize < b.l / blockSize;
}

void add(int p) {
    /// Add p'th element, update answer based on the effect
}

void remv(int p) {
    /// Remove p'th element, update answer based on the effect
}

void MO(){
    sort(qList+1, qList+Q+1, cmp);
    int curL = 0, curR = 0;

    for (int i = 1; i <= Q; i++) {
        int L = qList[i].l, R = qList[i].r;
        while (curL < L) {
            if (curL != 0) remv(curL);
            curL++;
        }
        while (curL > L) {
            curL--;
            add(curL);
        }
        while (curR < R) {
            curR++;
            add(curR);
        }
        while (curR > R) {
            remv(curR);
            curR--;
        }
        res[qList[i].id] = ans;
    }
}
