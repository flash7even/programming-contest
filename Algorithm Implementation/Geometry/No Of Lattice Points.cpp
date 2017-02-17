/// Find No of lattice points inside a triangle and also on a line.

LL X1,X2,X3,Y1,Y2,Y3;

LL GCD(LL a,LL b){
	if(b == 0) return a;
	return GCD(b,a%b);
}

LL Area(){
	return abs(X1*(Y2-Y3) + X2*(Y3-Y1) + X3*(Y1-Y2));
}

/// Find no of integer points on a line.
LL latticePointsOnLine(LL X1, LL Y1, LL X2, LL Y2){
	return GCD(abs(X1 - X2), abs(Y1 - Y2));
}

LL latticePointsOnTriangle(){
	LL b = GCD(abs(X1 - X2), abs(Y1 - Y2))
	       + GCD(abs(X2 - X3), abs(Y2 - Y3))
	       + GCD(abs(X3 - X1), abs(Y3 - Y1));
	return b;
}

/// Find no of lattice points inside a triangle.
LL runPicksTheorem(){
	LL cnt = (Area() - latticePointsOnTriangle() + 2)/2;
	return cnt;
}
