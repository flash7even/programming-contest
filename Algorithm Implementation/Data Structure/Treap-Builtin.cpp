#include <bits/stdc++.h>
using namespace std;

/// Importing policy_based_data_structure:

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

/// Importing ends here.

/// struct for declaring struct type pb_ds:

struct vals{
    int num;
    int typ;
    vals(int a, int b){
        num = a;
        typ = b;
    }
    bool operator <(const vals& other) const {
		return num > other.num; /// num is the value on what basis it'll get sorted.
	}
};

/// typedef original name to pb_ds for simplicity:
typedef tree <int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pb_ds;

/// struct type pb_ds:
typedef tree <vals, null_type, less<vals>, rb_tree_tag, tree_order_statistics_node_update> pb_ds_st;

/// Supports all the operations of a set including two additional features:
/// 1. find_by_order(k) # Returns an iterator pointing to the k-th smallest element (zero based).
/// 2. order_of_key(k) # Returns the number of elements strictly smaller than k.

int main(){
    /// Declaring a pb_ds(policy based ds):
    pb_ds treap;
    treap.insert(2); /// Insert an element
    treap.insert(5);
    cout << treap.order_of_key(5) << endl; /// Returns number of elements smaller than k
    pb_ds::iterator it = treap.find_by_order(0); /// Returns iterator pointing to the k-th smallest element
    cout << *it << endl; /// Print the element
    treap.clear(); /// Clear the treap

    /// Struct type policy based ds:
    pb_ds_st treap_st;
    treap_st.insert(vals(10,1));
    treap_st.insert(vals(20,2));
    /// Iterate though the elements (similar to a set)
    for(pb_ds_st::iterator it = treap_st.begin(); it != treap_st.end(); it++){
        vals v = *it;
        cout << v.num << " " << v.typ << endl;
    }
    return 0;
}
