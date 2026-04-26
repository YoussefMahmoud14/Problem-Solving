/*
Given a size N sequence A0, A1, ... , An-1. Process the following Q queries in order:
  L R X : Print the number and the sum of the elements among al, al+1, ... , ar-1 that are not greater than x
*/
// author:  -Abosalem-
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define ll long long
#define all(v) v.begin(),v.end()
using namespace std;
const int OO = 1e15+9;
const int limit = 1e18,  N = 21 , mod=1e9+7;

///==========================================


// merge sort tree
struct SegTree{
private:

#define L ((2*node)+1)
#define R ((2*node)+2)
#define mid ((lnode+rnode)/2)


    int tree_size ;
    vector<vector<int>> tree ;
    vector<vector<int>> pref ;
    vector<int> merge(const vector<int> &left , const vector<int>& right ) {
        int n =(int) left.size() , m=(int)right.size();
        vector<int> ans(n+m) ;
        int i=0 , j=0 , k=0 ;
        while (i < n && j < m) {
            if(left[i] < right[j])
                ans[k++] = left[i++];
            else
                ans[k++] = right[j++];
        }

        while (i < n)
            ans[k++] = left[i++];
        while (j < m)
            ans[k++] = right[j++];

        return ans ;

    }

    void build(int node , int lnode , int rnode , vector<int>&arr) {
        if(lnode == rnode) {
            if(lnode < arr.size()) {
                tree[node] = {arr[lnode]} ;
                pref[node] = {arr[lnode]} ;
            }
            return ;
        }

        build(L , lnode  , mid , arr) ;
        build(R , mid+1 , rnode , arr) ;
        tree[node] = merge(tree[L] , tree[R]);

        if(tree[node].empty()) return;

        pref[node].resize(tree[node].size());
        pref[node][0] = tree[node][0];
        for(int i = 1; i < tree[node].size(); i++){
            pref[node][i] = pref[node][i-1] + tree[node][i];
        }

    }

    // return num and sum of element less than or equal val int range from l to r
    pair<int,int> query(int node , int lnode , int rnode , int lq , int rq , int val) { // num , sum

        if(rnode < lq || lnode > rq) return {0,0} ;
        if(lnode >= lq && rnode <= rq) {
            int k = upper_bound(tree[node].begin(), tree[node].end(), val ) - tree[node].begin();
            if(k == 0) return {0,0};
            return {k , pref[node][k-1]} ;
        }
        auto left = query(L , lnode , mid , lq, rq , val) ;
        auto right = query(R , mid+1 , rnode , lq , rq , val) ;
        return {left.first +  right.first , left.second +  right.second} ;

    }




public:
    SegTree(vector<int>&v) {
        int n = v.size() ;
        tree_size=1 ;
        while(tree_size < n) tree_size <<= 1;
        tree.assign(2*tree_size , {}) ;
        pref.assign(2*tree_size , {}) ;
        build(0 , 0 , tree_size-1 , v);
    }

    pair<int,int> query(int l , int r , int val) {
        return query(0,0,tree_size-1 , l , r , val) ;
    }



#undef L
#undef R
#undef mid


};

///=====================================

void solve() {

    int n , q ; cin >> n >> q ;
    vector<int> arr(n) ;
    for(int i=0 ; i<n ; ++i) cin >> arr[i] ;
    SegTree st(arr) ;
    while(q--) {
        int l , r , val ; cin >> l >> r >> val ;
        if(r == l) {cout << 0 << ' ' << 0 << endl ; continue ;}
        auto [num , sum] = st.query(l , r - 1, val) ;
        cout << num << ' ' << sum << endl ;

    }



}



signed main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    // freopen("galactic.in", "r", stdin);
    int t = 1; // cin >> t;

    while (t--) {
        solve() ;
    }


    return 0;
}
