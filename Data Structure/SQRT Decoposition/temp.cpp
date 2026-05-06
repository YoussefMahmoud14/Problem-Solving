// update point and query num of element <= x
struct SQRT {
// 0-indexed
// to know the idx i in any block --> i / SQ
// to know the firs element in the block when you have any idx --> i - i%SQ

    int SQ = 350 , sz;
    int ign = 1e9+7 ;
    vector<vector<int> > B ;
    vector<int> arr ;

    SQRT(vector<int>&v) { // build
        sz = (int)v.size() ;
        B.resize(SQ , {}) ;
        for(int i=0 ; i<sz ; ++i) {
            B[i/SQ].emplace_back(v[i]) ;
        }
        arr = v;
        for(auto &b : B) {
            sort(all(b)) ;
        }
    }

    void update(int idx , int val) {
        int start = idx - (idx%SQ) ;
        int end = min(start + SQ - 1 , sz - 1) ;
        B[idx / SQ].clear() ;
        for(int i=start ; i<= end ; ++i) {
            if(idx == i) {
                arr[i] = val ;
            }
            B[i / SQ].emplace_back(arr[i]) ;
        }
        sort(all(B[idx / SQ]) ) ;

    }

    int query(int l , int r , int x ) { // num of element <= x
        int ans = 0 ;

        while(l <= r && l%SQ != 0) {
            ans += (arr[l] <= x)  ;
            l++ ;
        }

        while(l + SQ - 1 <= r) {
            int up = upper_bound(all(B[l / SQ]) , x) - B[l / SQ].begin() ;
            ans += up ;
            l += SQ ;
        }

        while(l <= r) {
            ans += (arr[l] <= x)  ;
            l++ ;
        }
        return ans ;
    }
};
