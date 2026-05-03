/*
1. Increase the first value in range [a, b] by 1, the second value by 2, the third value by 3, and so on.
--more general add the first value in [a, b] by a , the second value by a+2*(d) , the third value by a+3*d
2. Calculate the sum of values in range [a, b].

*/
struct Node {
    int sum , mn ;
    int a , d ; // a -> start , d -> diff
    int lazy  ;
    bool isLazy  ;

    Node() {
        sum=0 ;
        a = d = lazy = 0 ;
        isLazy = 0 ;

    }
    Node(int val) {
        a =  0 ; d = 0 ;
        lazy = 0 ;
        sum = val ;
        isLazy = 0 ;

    }

    void update(int na , int nd , int lnode , int rnode ) {
        int len = (rnode - lnode + 1) ;
        sum += (na*len) + nd*(len*(len-1)/2) ;
        a += na ;
        d += nd ;
        isLazy = 1 ;
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

    void push(int node , int lnode , int rnode) {
        if(lnode == rnode || !tree[node].isLazy) return ;

        tree[L].update(tree[node].a , tree[node].d , lnode , mid) ;
        tree[R].update( tree[node].a + tree[node].d * (rnode - lnode +1)/2,
                        tree[node].d , mid+1 , rnode) ;
        tree[node].isLazy = 0 ;
        tree[node].a = tree[node].d = 0 ;
    }
    void update(int node ,  int lnode , int rnode , int lq , int rq , int a , int d) {
        push(node , lnode , rnode) ;
        if(rnode < lq || lnode > rq) return  ;
        if(lnode >= lq && rnode <= rq) {
            tree[node].update(a+ (lnode - lq)*d ,d , lnode , rnode) ;
            return ;
        }

        update(L , lnode , mid , lq , rq , a , d) ;
        update(R , mid+1 , rnode , lq , rq , a , d ) ;
        tree[node] = merge(tree[L] , tree[R]) ;

    }

    Node query(int node , int lnode , int rnode , int lq , int rq) {
        push(node , lnode , rnode) ;
        if(rnode < lq || lnode > rq) return Node() ;
        if(lnode >= lq && rnode <= rq) {
            return tree[node] ;
        }
        Node left = query(L , lnode , mid , lq, rq) ;
        Node right = query(R , mid+1 , rnode , lq , rq) ;
        return merge(left, right) ;
    }



public:
    SegTree(vector<int>&v) {
        int n = v.size() ;
        tree_size=1 ;
        while(tree_size < n) tree_size <<= 1;
        tree.assign(2*tree_size , Node()) ;
        build(0 , 0 , tree_size-1 , v);
    }

    void update(int l,int r , int a , int d) {
        update(0,0,tree_size-1 , l,r , a , d  ) ;
    }
    int query(int l,int r) {
        return query(0,0,tree_size-1 , l,r).sum ;
    }


#undef L
#undef R
#undef mid


};




///=====================================

void solve() {

    int n , q ; cin >> n >> q;
    vector<int> arr(n,0) ;
    for(int i=0 ; i<n ; ++i) cin >> arr[i] ;
   // cin >> q ;
    SegTree st(arr) ;
    while(q--) {
        int op; cin >> op ;
        if(op == 2) {
            int l , r ; cin >> l >> r ;
            l-- ; r-- ;
            cout << st.query(l , r) << endl ;
        }
        else {
            int l , r , a , d ; cin >> l >> r >> a >> d ;
            st.update(l-1,r-1,a,d) ;
        }
    }

}
