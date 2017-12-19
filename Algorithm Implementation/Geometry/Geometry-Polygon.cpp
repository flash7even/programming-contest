/// Polygon Geometry

struct polygonGeometry{
    int N; /// Number of total points
    vector<Point> polygon; /// Contains all the polygon points

    void clear(){
        polygon.clear();
    }

    bool onSegment(Point P, Point Q, Point R){
        if (R.x >= min(P.x, Q.x) && R.x <= max(P.x, Q.x) && R.y >= min(P.y, Q.y)
                && R.y <= max(P.y, Q.y)){
            return true;
        }else{
            return false;
        }
    }

    bool doIntersect(Point P1, Point P2, Point P3, Point P4, bool &onLine){
        int o1 = orientation(P1, P2, P3);
        int o2 = orientation(P1, P2, P4);
        int o3 = orientation(P3, P4, P1);
        int o4 = orientation(P3, P4, P2);

        if (o1 != o2 && o3 != o4 && o1 != 0 && o2 != 0 && o3 != 0 && o4 != 0){
            return true;
        }

        if (o1 == 0 && onSegment(P1, P2, P3)){
            onLine = true; /// Change here, if point on line is not allowed
            return true;
        }

        if (o2 == 0 && onSegment(P1, P2, P4)) return true;
        if (o3 == 0 && onSegment(P3, P4, P1)) return true;
        if (o4 == 0 && onSegment(P3, P4, P2)) return true;
        return false;
    }

    /// Check if point P lie inside polygon
    bool isInsidePolygon(Point P) {
        Point Q;
        Q.y = P.y + 1e9; /// Change here, depends on maximum co ordinate value
        Q.x = P.x + 1e9+1;
        bool onLine = false; /// To check if the point lie on any segment
        int cnt = 0;
        for (int i = 0; i + 1 < polygon.size(); i++){
            if (doIntersect(polygon[i], polygon[i + 1], P, Q, onLine)) cnt++;
        }
        if (onLine) return true; /// Change here, if point on line is not allowed
        if (cnt % 2 == 1) return true;
        return false;
    }

    /// Given a convex hull it returns the center of masses or gravity of it
    Point centerOfMass(vector<Point> P) {
        double area = polygonArea(P);
        double cx = 0, cy = 0;
        int sz = P.size();
        for (int i = 0; i < sz; ++i) {
            Point cur = P[i];
            Point nxt = P[(i + 1) % sz];
            cx += (cur.x + nxt.x) * (cur.x * nxt.y - cur.y * nxt.x);
            cy += (cur.y + nxt.y) * (cur.x * nxt.y - cur.y * nxt.x);
        }
        cx = cx/(6.0 * area);
        cy = cy/(6.0 * area);
        return Point(cx, cy);
    }

}polygonGeo;
