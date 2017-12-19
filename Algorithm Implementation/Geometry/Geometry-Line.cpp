/// Line Geometry
/// Use necessary functions related to line
/// Don't forget to include base template

struct lineGeometry{

    /// Returns A,B,C of the equation Ax + By = C.
    piii lineEquation(Point P1, Point P2){
        int A = P2.y - P1.y;
        int B = P1.x - P2.x;
        int C = A * P1.x + B * P1.y;
        return MP(MP(A,B), C);
    }

    /// Find minimum distance between C and line/segment (A - B)
    double pointToLineDistance(Point A, Point B, Point C, bool isSeg) {
        double d = (double)crossABC(A, B, C) / dist(A, B);
        if (isSeg) { /// AB is a line segment
            if (dotABC(A, B, C) > 0) return dist(B, C);
            if (dotABC(B, A, C) > 0) return dist(A, C);
        }
        return FABS(d);
    }

    /// Check if R lies on line segment (P - Q)
    bool onSegment(Point P, Point Q, Point R) {
        if (R.x >= min(P.x, Q.x) && R.x <= max(P.x, Q.x) &&
                R.y >= min(P.y, Q.y) && R.y <= max(P.y, Q.y)){
            return true;
        } else {
            return false;
        }
    }

    /// Check if line segment (P1-P2) and line segment (P3-P4) intersect
    bool segmentIntersect(Point P1, Point P2, Point P3, Point P4) {
        int o1 = orientation(P1, P2, P3);
        int o2 = orientation(P1, P2, P4);
        int o3 = orientation(P3, P4, P1);
        int o4 = orientation(P3, P4, P2);

        if (o1 != o2 && o3 != o4 && o1 != 0 && o2 != 0 && o3 != 0 && o4 != 0){
            return true;
        }

        if (o1 == 0 && onSegment(P1, P2, P3)) return true;
        if (o2 == 0 && onSegment(P1, P2, P4)) return true;
        if (o3 == 0 && onSegment(P3, P4, P1)) return true;
        if (o4 == 0 && onSegment(P3, P4, P2)) return true;
        return false;
    }

    /// Find intersection point of line (P1-P2) and (P3-P4)
    void intersectionPoint(Point P1, Point P2, Point P3, Point P4){
        piii L1 = lineEquation(P1,P2);
        int A1 = L1.ff.ff, B1 = L1.ff.ss, C1 = L1.ss;

        piii L2 = lineEquation(P3,P4);
        int A2 = L2.ff.ff, B2 = L2.ff.ss, C2 = L2.ss;

        int dif = A1*B2 - A2*B1; /// Slope difference of the two lines

        if(dif == 0){ /// Lines are either collinear or parallel.
            vector<Point> List;
            List.pb(P1); List.pb(P3); List.pb(P4); List.pb(P2);
            if (polygonArea(List) == 0){
                printf("Collinear\n");
            }else{
                printf("Parallel\n");
            }
        }else{
            double x = (B2 * C1 - B1 * C2) / dif;
            double y = (A1 * C2 - A2 * C1) / dif;
            cerr << x << " " << y << endl; /// Return if needed.
        }
    }

    /// Find a point C on line AB such that distance from A to C is D.
    Point pointAtDistanceD(Point A, Point B, double D){
        Point vecAB,C;
        vecAB.x = B.x - A.x;
        vecAB.y = B.y - A.y;
        double norm = sqrt(SQ(vecAB.x) + SQ(vecAB.y));
        vecAB.x /= norm;
        vecAB.y /= norm;
        C.x = A.x + D*vecAB.x; /// To find a point D distance away but outside the line then minus here.
        C.y = A.y + D*vecAB.y;
        return C;
    }

}lineGeo;
