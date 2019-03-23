int extended_euclid(int A,int B,int * X,int * Y){
	int a = A,b = B,x = 0,y = 1,u = 1,v = 0;
	while(a!=0){
		int qtnt = b/a;
		int rem = b%a;
		int m = x - u*qtnt;
		int n = y - v*qtnt;
		b = a;a = rem;
		x = u,y = v;
		u = m;v = n;
	}
	*X = x,*Y = y;
	return b;
}
