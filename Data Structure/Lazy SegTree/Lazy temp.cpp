// add val to range and print min in range
struct Node {
    int sum , mn ;
    int lazy ;
    bool isLazy ;
    Node() {
        mn = OO ;
        sum= lazy = 0 ;
        isLazy = 0 ;
    }
    Node(int val) {
        sum = mn = val ;
        lazy = 0 ;
        isLazy = 0 ;
    }

    void update(int val , int lnode , int rnode ) {
        mn += val ;
        lazy += val ;
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
        ret.mn = min(left.mn , right.mn ) ;
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
        if(lnode == rnode || tree[node].isLazy == 0) return ;
        tree[L].update(tree[node].lazy , lnode , mid) ;
        tree[R].update( tree[node].lazy, mid+1 , rnode ) ;
        tree[node].isLazy = 0 ;
        tree[node].lazy = 0 ;
    }
    void update( int node ,  int lnode , int rnode , int lq , int rq, int val) {
        push(node , lnode , rnode) ;
        if(rnode < lq || lnode > rq) return  ;
        if(lnode >= lq && rnode <= rq) {
            tree[node].update(val , lnode , rnode) ;
            return ;
        }

        update(L , lnode , mid , lq , rq , val) ;
        update(R , mid+1 , rnode , lq , rq , val) ;
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

    void update(int l,int r , int val) {
        update(0,0,tree_size-1 , l,r,val) ;
    }
    int query(int l,int r) {
        return query(0,0,tree_size-1 , l,r).mn ;
    }


#undef L
#undef R
#undef mid


};
