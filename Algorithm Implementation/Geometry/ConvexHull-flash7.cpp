/// Convex Hull
/// Take input points in polygon vector and assign N
/// Call grahamScan to get convex hull in vector hull

Point lowerLeft;

bool convexCmp(Point X, Point Y) {
    LL ret = orientation(lowerLeft, X, Y);
    if (ret == 0) {
        LL d1 = sqrDist(lowerLeft, X);
        LL d2 = sqrDist(lowerLeft, Y);
        return (d1 < d2);
    } else if (ret == 2){
        return true;
    } else {
        return false;
    }
}

struct convexHull{

    int N; /// Number of total points
    stack<Point> st;
    vector<Point> polygon; /// Contains all the polygon points
    vector<Point> hull; /// Convex hull points (all distinct)
    /// Reverse hull depending on necessity

    void clear(int L){
        polygon.clear();
        hull.clear();
        N = L;
    }

    Point nextToTop() {
        Point P = st.top();
        st.pop();
        Point res = st.top();
        st.push(P);
        return res;
    }

    void grahamScan(){
        int ymin = polygon[0].y, idx = 0;
        for (int i = 1; i < N; i++) {
            if (polygon[i].y < ymin || (polygon[i].y == ymin &&
                            polygon[i].x < polygon[idx].x)) {
                ymin = polygon[i].y;
                idx = i;
            }
        }

        swap(polygon[0], polygon[idx]);
        lowerLeft = polygon[0];

        sort(polygon.begin()+1, polygon.end(), convexCmp);
        st.push(polygon[0]);

        for (int i = 1; i < N; i++) {
            while (st.size() > 1){
                if(orientation(nextToTop(),st.top(), polygon[i]) == 2) break;
                st.pop();
            }
            st.push(polygon[i]);
        }
        while (!st.empty()) {
            hull.pb(st.top());
            st.pop();
        }
    }

}convexhull;
