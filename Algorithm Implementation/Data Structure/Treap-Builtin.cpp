/// Importing policy_based_data_structure:
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
/// Importing ends here.

struct vals{ /// struct for declaring struct type pb_ds:
    int num;
    int typ;
    vals(int a, int b){
        num = a;
        typ = b;
    }
    bool operator <(const vals& other) const {
		return num > other.num;
	}
};

/// Supports all the operations of a set including two additional features:
/// 1. find_by_order(k) # Returns an iterator pointing to the k-th smallest element (zero based).
/// 2. order_of_key(k) # Returns the number of elements strictly smaller than k.

int main(){
    /// typedef original name to pb_ds for simplicity:
    typedef tree <int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pb_ds;
    /// Ordered Set
    pb_ds treap;

    treap.insert(2); /// Insert an element
    treap.insert(3);

    cout << treap.order_of_key(5) << endl; /// Returns number of elements smaller than k

    pb_ds::iterator it = treap.find_by_order(0); /// Returns an iterator pointing to the k-th smallest element
    cout << *it << endl; /// Print the element

    /// Iterate though the elements (similar to a set)
    for(pb_ds::iterator it = treap.begin(); it != treap.end(); it++){
        cout << *it << endl;
    }

    treap.erase(2); /// Erase an element
    treap.clear(); /// Clear the treap

    /// Struct type pb_ds. Ordering depends on the operator overloading inside the struct.
    typedef tree <vals, null_type, less<vals>, rb_tree_tag, tree_order_statistics_node_update> pb_ds_st;

    /// Ordered Multiset. Notice the less_equal<int> parameter.
    typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;

    ordered_multiset tmset;
    tmset.insert(2);
    tmset.insert(2);
    /// Erasing is very tricky in Ordered Multiset
    tmset.erase(tmset.find_by_order(tmset.order_of_key(2))); /// Erase 2 (Just one of the 2's get erased)

    /// Pair <int,int> type Ordered Set
    typedef tree<pair<int, int>, null_type, less_equal<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> ordered_pair;

}
