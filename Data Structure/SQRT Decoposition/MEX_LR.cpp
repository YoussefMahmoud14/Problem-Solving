struct Query {
    int l, r, idx;
};

struct Mo {
    int sz, MO_SQ, VAL_SQ;
    vector<int> arr, freq, RET, B;

    Mo(vector<int> &v, int q) {
        arr = v;
        sz = (int)v.size();
        MO_SQ = sz / max(1LL, (int)sqrt(q)) + 7;
        VAL_SQ = sqrt(sz) + 5;
        freq.assign(sz + 7, 0);
        B.assign((sz / VAL_SQ) + 7, 0);
    }

    void add(int idx) {
        if (arr[idx] > sz) return;
        freq[arr[idx]]++;
        if (freq[arr[idx]] == 1) {
            B[arr[idx] / VAL_SQ]++; 
        }
    }

    void rem(int idx) {
        if (arr[idx] > sz) return;
        freq[arr[idx]]--;
        if (freq[arr[idx]] == 0) {
            B[arr[idx] / VAL_SQ]--; 
        }
    }

    int get_mex() {
        for (int i = 0; ; ++i) {
            int L = i * VAL_SQ;
            if (L > sz) break;
            int R = min(sz, L + VAL_SQ - 1);
            if (B[i] == R - L + 1) continue;
            for (int j = L; j <= R; ++j) {
                if (freq[j] == 0) return j;
            }
        }
        return sz + 1;
    }
    void solve(vector<Query> &QR) {
        if(QR.empty()) return ;
        RET.resize(QR.size());

        sort(all(QR), [&](auto &a, auto &b) {
            int A = a.l / MO_SQ;
            int B = b.l / MO_SQ;
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
            RET[idx] = get_mex( ) ;

        }

        for (int i = 0; i < RET.size(); ++i) {
            cout << RET[i] << endl ;
        }
    }
};

