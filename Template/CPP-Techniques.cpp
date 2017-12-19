/// Operator Overloading
struct node {
	int value;
	/// Process in decreasing order
	bool operator <(const node& o) const{
		if(value<o.value) return true;
		return false;
	}
};

/// Min Priority Queue
priority_queue<int, vector<int>, greater<int> > minPQ;

/// Merge two sorted vector v1 and v2 into v
merge(v1.begin(),v1.end(),v2.begin(),v2.end(),v.begin());


/// lower_bound: Returns the position of the smallest element not less than x
int pos = lower_bound(v.begin(),v.end(),x) - v.begin();
/// upper_bound: Returns the position of the smallest element greater than x

/// Using bit sets:
bitset<SZ> bits; /// SZ = Number of bits
bits.set(); /// Set all bits to one
bits.set(p,1) /// Set p'th bit to 1
bits.flip(p) /// Flip p'th bit
/// count() returns no of one bits

