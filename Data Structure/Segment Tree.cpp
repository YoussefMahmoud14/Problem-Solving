struct Node {
    int sum , mn ,GCD , mx;
    Node() {
        sum= 0 ;
        mx=-1 ;
        mn = 1e18 ;
        GCD = 0 ;
    }
    Node(int val) {
        sum=val ;
        mn = val; GCD = mx = val ;
    }


};

struct SegTree{
private:

#define L ((2*node)+1)
#define R ((2*node)+2)
#define mid ((lnode+rnode)/2)


    int tree_size ;
    vector<Node> tree ;

    Node merge(Node left , Node right) {
        Node ret ;
        ret.sum = left.sum + right.sum ;
        ret.mx = max(left.mx , right.mx ) ;
        ret.mn = min(left.mn , right.mn ) ;
       // ret.GCD = __gcd(left.GCD , right.GCD) ;
        return ret ;
    }
    void build(int node , int lnode , int rnode , vector<int>&arr) {
        if(lnode == rnode) {
            if(lnode < arr.size()) {
                tree[node] = arr[lnode] ;
            }
            return ;
        }

        build(L , lnode  , mid , arr) ;
        build(R , mid+1 , rnode , arr) ;
        tree[node] = merge(tree[L] , tree[R]) ;
    }

    void update(int idx , int val , int node ,  int lnode , int rnode) {
        if(lnode == rnode) {
            tree[node] = Node(val) ;
            return ;
        }

        if(idx <= mid ) {
            update(idx , val , L , lnode , mid) ;
        }
        else {
            update(idx , val , R , mid+1 , rnode ) ;
        }

        tree[node] = merge(tree[L] , tree[R]) ;
    }

    /// use in seg tree beats
    void update_range(int node , int lnode , int rnode , int lq , int rq , int val ) {
        if(rnode < lq || lnode > rq || tree[node].mx < val) {
            return ;
        }

        if(lnode == rnode) {
            tree[node].sum %= val ;
            tree[node].mx %= val ;
            return ;
        }

        update_range(L , lnode , mid , lq , rq , val) ;
        update_range(R , mid+1 , rnode , lq , rq , val) ;

        tree[node] = merge(tree[L] , tree[R]) ;
    }
    
    Node query(int node , int lnode , int rnode , int lq , int rq) {
        if(rnode < lq || lnode > rq) return Node() ;
        if(lnode >= lq && rnode <= rq) {
            return tree[node] ;
        }
        Node left = query(L , lnode , mid , lq, rq) ;
        Node right = query(R , mid+1 , rnode , lq , rq) ;
        return merge(left, right) ;
    }

    int find_idx(int node , int lnode , int rnode , int val) { // first idx >= val
        if(lnode == rnode) {
            return lnode ;
        }
        int left = tree[L].mx ;
        if(left >= val) {
            return find_idx(L , lnode , mid , val);
        }
        else {
            return find_idx(R , mid+1 , rnode , val);
        }
    }

public:
    SegTree(vector<int>&v) {
        int n = v.size() ;
        tree_size=1 ;
        while(tree_size < n) tree_size <<= 1;
        tree.assign(2*tree_size , Node()) ;
        build(0 , 0 , tree_size-1 , v);
    }

    void update(int idx , int val) {
        update(idx,val,0,0,tree_size-1) ;
    }
    int query(int l,int r) {
        return query(0,0,tree_size-1 , l,r).sum ;
    }

    void update_range(int l , int r , int val ) {
        update_range(0,0,tree_size-1 , l,r , val) ;
    }
    int find_idx(int val) {
        return find_idx(0,0,tree_size-1 , val) ;
    }

#undef L
#undef R
#undef mid


};
