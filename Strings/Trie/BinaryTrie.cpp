struct BinaryTrie {
    struct Node {
        Node *child[2] ;
        int freq[2] ;
        Node() {
            child[0] = child[1] = nullptr ;
            freq[0] = freq[1] = 0 ;
        }
    };

    Node *root = new Node() ;
    void insert(int num) {

        Node *cur = root ;
        for(int i = 29 ; i>=0 ; --i) {
            int idx = (num >> i) & 1 ;
            if(cur->child[idx] == nullptr) {
                cur->child[idx] = new Node() ;
            }
            cur->freq[idx]++ ;
            cur = cur->child[idx] ;
        }
    }

    void Erase(int num , int i , Node*cur) {
        if(i < 0) return ;

        int idx = (num >> i) & 1 ;
        Erase(num , i-1 , cur -> child[idx]) ;

        cur -> freq[idx]-- ;
        if(!cur->freq[idx]) {
            delete cur-> child[idx] ;
            cur->child[idx] = nullptr ;
        }
    }

    void Erase(int num) {
        return Erase(num , 29 , root) ;
    }
    int mxXOR(int num) { //
        Node *cur = root ;
        int ret = 0 ;

        for(int i=29 ; i>=0 ; --i) {
            int idx = (num >> i) & 1 ;
            if(cur -> child[idx^1] ) {
                ret|=(1<<i) ;
                cur = cur-> child[idx^1] ;
            }
            else {
                cur = cur -> child[idx] ;
            }
        }
        return ret ;
    }


};
