#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int , null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> OrderedSet;
// multi -> less_equal
// s.order_of_key(x); --> return number of element that less than x
// cout << *s.find_by_order(k); --> return kth number .. {1, 2, 3} -- *s.find_by_order(1) = 2 ;

void erase(OrderedSet &t, int v){
    int rank = t.order_of_key(v);
    auto it = t.find_by_order(rank);
    t.erase(it);
}
