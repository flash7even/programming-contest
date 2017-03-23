/**
	The lattitude and longitude are given with respect to the earth radius.
	Which is R = 6378.
	Find the minimum distance between the two points.
	UVa : 10075
**/


/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

double dist(double a_lat, double b_lat, double a_long, double b_long) {
	/// Angels must be converted into radian.
	return R * acos( cos(a_lat)*cos(b_lat)*cos(a_long - b_long)
					 + sin(a_lat)*sin(b_lat));
}

int main(){
	double a_lat,a_long,b_lat,b_long;
	cin >> a_lat >> a_long >> b_lat >> b_long;
    cout << dist(a_lat,b_lat,a_long,b_long) << endl;
    return 0;
}
