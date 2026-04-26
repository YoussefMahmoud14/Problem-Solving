// merge sort tree
struct SegTree{
private:

#define L ((2*node)+1)
#define R ((2*node)+2)
#define mid ((lnode+rnode)/2)


    int tree_size ;
    vector<vector<int>> tree ;

    vector<int> merge(const vector<int> &right , const vector<int>& left ) {
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
            }
            return ;
        }

        build(L , lnode  , mid , arr) ;
        build(R , mid+1 , rnode , arr) ;
        tree[node] = merge(tree[L] , tree[R]) ;
    }

    // return num of element less than val int range from l to r
    int less(int node , int lnode , int rnode , int lq , int rq , int val) {

        if(rnode < lq || lnode > rq) return 0 ;
        if(lnode >= lq && rnode <= rq) {
            return lower_bound(tree[node].begin(), tree[node].end(), val ) - tree[node].begin();
        }
        int left = less(L , lnode , mid , lq, rq , val) ;
        int right = less(R , mid+1 , rnode , lq , rq , val) ;
        return left +  right ;


    }

    int kth(int l , int r , int k) {
        int lo = (int)-1e9-5 , hi = (int)1e9+5 , ans;
        while(lo <= hi){
            int m = (lo + hi) >> 1;
            int cnt = less(l, r, m + 1);
            if(cnt > k){
                ans = m;
                hi = m - 1;
            }
            else {
                lo = m + 1;
            }
        }

        return ans;
    }


public:
    SegTree(vector<int>&v) {
        int n = v.size() ;
        tree_size=1 ;
        while(tree_size < n) tree_size <<= 1;
        tree.assign(2*tree_size , {}) ;
        build(0 , 0 , tree_size-1 , v);
    }

    int less(int l , int r , int val) {
        return less(0,0,tree_size-1 , l , r , val) ;
    }

    int Kth(int l , int r , int k) {
        return kth(l , r , k) ;
    }


#undef L
#undef R
#undef mid


};
