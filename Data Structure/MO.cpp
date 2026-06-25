struct Query {
    int l , r , idx ;
};

struct Mo {

    int sz , ans , SQ ;
    vector<int> arr , freq , RET ;

    Mo(vector<int> &v , int q) {
        arr = v ;
        sz = (int)v.size() ;
        ans = 0 ; // nuteral
        SQ = sz / (int)sqrt(q) + 3 ; // better than sqrt(n)
        freq.assign(1e6+7 , 0) ;
    }
    void add(int idx) {
        ans -= (freq[arr[idx]] / 2 ) ; // 1- remove the last contribution from the ans
        freq[arr[idx]]++ ;             // 2- update
        ans += (freq[arr[idx]] / 2 ) ; // 3- add the new contribution to the ans
    }
    void rem(int idx) {
        ans -= (freq[arr[idx]] / 2 ) ;
        freq[arr[idx]]-- ;
        ans += (freq[arr[idx]] / 2 ) ;
    }
    void solve(vector<Query> &QR) {
        if(QR.empty()) return ;
        RET.resize(QR.size());

        sort(all(QR), [&](auto &a, auto &b) {
            int A = a.l / SQ;
            int B = b.l / SQ;
            if(A != B) return A < B;
            return (A & 1) ? a.r > b.r : a.r < b.r;
        });

        int curL = QR[0].l , curR = QR[0].l ;
        add(curL) ;
        for(auto [lq , rq , idx] : QR) {
            while (curR < rq) add(++curR) ;
            while (curL < lq) rem(curL++) ;
            while (curL > lq) add(--curL) ;
            while (curR > rq) rem(curR--);
            RET[idx] = ans ;

        }
      
        for (int i = 0; i < RET.size(); ++i) {
            cout << RET[i] << endl ;
        }
    }
};
