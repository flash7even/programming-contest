const int Size = 50005; /// Maximum number of points
const int LGN = 25; /// log(Size)

/// Given N points find the closest pair among them
/// Call cpair.closestPairOfPoints()

struct RET{
    double res;
    int u;
    int v;
    RET(double a, int b, int c){
        res = a;
        u = b;
        v = c;
    }
};

struct Point {
    double x, y;
    int idx;
    Point(){}
    Point(double a, double b, int i){
        x = a, y = b, idx = i;
    }
};

double dist(Point P, Point Q) {
    double res = SQ(P.x - Q.x) + SQ(P.y - Q.y);
    return sqrt(res);
}

int cmpX(Point a, Point b) {
    return (a.x < b.x);
}

int cmpY(Point a, Point b) {
    return (a.y < b.y);
}

Point xList[LGN][Size][2];
Point yList[LGN][Size][2];
Point strip[Size];
Point Px[Size+5];
Point Py[Size+5];

struct closestPair{

    RET bruteForce(int lvl, int sd, int N) {
        double Min = FLT_MAX;
        int u = 0, v = 0;
        for (int i = 0; i < N; ++i){
            for (int j = i + 1; j < N; ++j){
                if (dist(xList[lvl][i][sd], xList[lvl][j][sd]) < Min){
                    Min = dist(xList[lvl][i][sd], xList[lvl][j][sd]);
                    u = xList[lvl][i][sd].idx;
                    v = xList[lvl][j][sd].idx;
                }
            }
        }
        return RET(Min, u, v);
    }

    RET closestPairInStrip(int Sz, RET d) {
        double curMin = d.res;
        int u = d.u, v = d.v;
        for (int i = 0; i < Sz; ++i){
            for (int j = i + 1; j < Sz && (strip[j].y - strip[i].y) < curMin; ++j){
                if (dist(strip[i], strip[j]) < curMin){
                    curMin = dist(strip[i], strip[j]);
                    u = strip[i].idx;
                    v = strip[j].idx;
                }
            }
        }
        return RET(curMin, u, v);
    }

    RET findPoint(int lvl, int sd, int N) {
        if (N <= 3){
            return bruteForce(lvl, sd, N);
        }
        int mid = N / 2;
        Point midPoint = xList[lvl][mid][sd];
        int leftIdx = 0, rightIdx = 0;
        for (int i = 0; i < N; i++) {
            if (yList[lvl][i][sd].x <= midPoint.x) {
                yList[lvl+1][leftIdx++][0] = yList[lvl][i][sd];
            } else {
                yList[lvl+1][rightIdx++][1] = yList[lvl][i][sd];
            }
        }
        for (int i = 0; i < mid; i++) {
            xList[lvl+1][i][0] = xList[lvl][i][sd];
        }
        for (int i = mid; i < N; i++) {
            xList[lvl+1][i-mid][1] = xList[lvl][i][sd];
        }
        RET distLeft = findPoint(lvl+1, 0, mid);
        RET distRight = findPoint(lvl+1, 1, N - mid);
        RET curbest = distLeft;

        if(distLeft.res<distRight.res){
            curbest = distLeft;
        }else{
            curbest = distRight;
        }

        double minDist = curbest.res;
        int j = 0;
        for (int i = 0; i < N; i++){
            if (abs(yList[lvl][i][sd].x - midPoint.x) < minDist){
                strip[j] = yList[lvl][i][sd];
                j++;
            }
        }
        RET ncur = closestPairInStrip(j, curbest);
        if(curbest.res < ncur.res) return curbest;
        return ncur;
    }

    /// Returns an RET object which store the index(u, v) of the closest 2 points
    /// as well as their distance.
    /// Parameters: (Array of points, number of points)
    RET closestPairOfPoints(Point * P, int N) {
        for (int i = 0; i < N; i++) {
            Px[i] = P[i];
            Py[i] = P[i];
        }
        sort(Px, Px+N, cmpX);
        sort(Py, Py+N, cmpY);
        for (int i = 0; i < N; i++) {
            xList[0][i][0] = Px[i];
            yList[0][i][0] = Py[i];
        }
        return findPoint(0, 0, N);
    }

}cpair;
