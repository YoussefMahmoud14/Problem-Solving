// author:  -Abosalem-

///==========================================

struct Node {
    int sum , mn ;
    int lazy_set , lazy_add ;
    bool isLazySet , isLazyAdd ;
    Node() {
        mn = OO ;
        sum= lazy_set = lazy_add = 0 ;
        isLazySet = isLazyAdd = 0 ;
    }
    Node(int val) {
        sum = mn = val ;
        lazy_set = lazy_add = 0 ;
        isLazySet = isLazyAdd = 0 ;
    }

    void set( int lnode , int rnode , int val) {
        int len = (rnode - lnode + 1) ;
        sum = len * val ;
        lazy_set = val ;
        lazy_add = 0 ;
        isLazySet = 1 ;
        isLazyAdd = 0 ;
    }
    void add(int lnode , int rnode , int val) {
        int len = (rnode - lnode + 1) ;
        sum += len * val ;
        lazy_add += val  ;
        isLazyAdd = 1 ;
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
       // ret.mn = min(left.mn , right.mn ) ;
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
        if(lnode == rnode || (tree[node].isLazyAdd == 0 && tree[node].isLazySet == 0 )) return ;

        if(tree[node].isLazySet) {
            tree[L].set(lnode , mid ,tree[node].lazy_set );
            tree[R].set(mid+1 , rnode ,tree[node].lazy_set );
            tree[node].isLazySet = 0;
            tree[node].lazy_set = 0 ;
        }

        if(tree[node].isLazyAdd) {
            tree[L].add(lnode , mid ,tree[node].lazy_add );
            tree[R].add(mid+1 , rnode ,tree[node].lazy_add );
            tree[node].isLazyAdd = 0;
            tree[node].lazy_add = 0 ;
        }

    }
    void add( int node ,  int lnode , int rnode , int lq , int rq, int val) {
        push(node , lnode , rnode) ;
        if(rnode < lq || lnode > rq) return  ;
        if(lnode >= lq && rnode <= rq) {
            tree[node].add( lnode , rnode , val) ;
            return ;
        }

        add(L , lnode , mid , lq , rq , val) ;
        add(R , mid+1 , rnode , lq , rq , val) ;
        tree[node] = merge(tree[L] , tree[R]) ;

    }
    void set( int node ,  int lnode , int rnode , int lq , int rq, int val) {
        push(node , lnode , rnode) ;
        if(rnode < lq || lnode > rq) return  ;
        if(lnode >= lq && rnode <= rq) {
            tree[node].set( lnode , rnode , val) ;
            return ;
        }

        set(L , lnode , mid , lq , rq , val) ;
        set(R , mid+1 , rnode , lq , rq , val) ;
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

    void set(int l,int r , int val) {
        set(0,0,tree_size-1 , l,r,val) ;
    }
    void add(int l,int r , int val) {
        add(0,0,tree_size-1 , l,r,val) ;
    }
    int query(int l,int r) {
        return query(0,0,tree_size-1 , l,r).sum ;
    }


#undef L
#undef R
#undef mid


};
///=====================================
