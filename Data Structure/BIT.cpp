// 1-indexed
struct BIT { // 1-indexed

    int n;
    vector<long long> b;

    BIT(int sz) {
        n = 1;
        while(n < sz) n*=2 ;
        b.assign(n + 1, 0);
    }

    long long get(int idx) {
        long long res = 0;
        while (idx > 0) {
            res += b[idx];
            idx -= idx & -idx;
        }
        return res;
    }

    void add(int idx, int v) {
        while (idx <= n) {
            b[idx] += v;
            idx += idx & -idx;
        }
    }

    long long get(int l, int r) {
        return get(r) - get(l - 1);
    }

    long long get_idx(int idx) {
        return get(idx) - get(idx - 1);
    }

    void set(int idx, int v) {
        int old = get_idx(idx);
        add(idx, -old + v);
    }

    int lower_bound(long long sum) {
        int idx=0 ;
        for(int step = n ; step >= 1 ; step >>= 1) {
            if(b[idx + step] < sum) {
                sum -= b[idx + step] ;
                idx += step ;
            }
        }

        return idx + 1 ;
    }
};
