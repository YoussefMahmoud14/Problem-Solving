struct MultiSet {
    int n;
    vector<long long> b;

    // Constructor: initialize Fenwick Tree with size as next power of 2
    MultiSet (int sz) {
        n = 1;
        while (n < sz) n <<= 1;
        b.assign(n + 1, 0);
    }

    // add: update index by adding value (point update in Fenwick Tree)
    void add(int idx, int val) {
        while (idx <= n) {
            b[idx] += val;
            idx += idx & -idx;
        }
    }

    // get(idx): returns prefix sum from 1 to idx
    long long get(int idx) {
        long long res = 0;
        while (idx > 0) {
            res += b[idx];
            idx -= idx & -idx;
        }
        return res;
    }

    // get(l, r): returns sum in range [l, r]
    long long get(int l, int r) {
        return get(r) - get(l - 1);
    }

    // get_idx(idx): returns the exact value at index idx
    long long get_idx(int idx) {
        return get(idx) - get(idx - 1);
    }

    // lower_bound(sum): finds smallest index such that prefix sum >= sum
    int lower_bound(long long sum) {
        int idx = 0;
        for (int step = n; step > 0; step >>= 1) {
            if (b[idx + step] < sum) {
                sum -= b[idx + step];
                idx += step;
            }
        }
        return idx + 1;
    }

    // insert(val): insert one occurrence of value val
    void insert(int val) {
        add(val, 1);
    }

    // insert(val, cnt): insert cnt occurrences of value val
    void insert(int val, int cnt) {
        add(val, cnt);
    }

    // erase(val): remove one occurrence of value val if exists
    void erase(int val) {
        int cnt = get_idx(val);
        if(cnt)
            add(val, -1);
    }

    // erase(val, cnt): remove up to cnt occurrences of value val
    void erase(int val, int cnt) {
        int mx = get_idx(val);
        cnt = min(cnt, mx);
        add(val, -cnt);
    }

    // operator[]: returns the k-th smallest element
    int operator[](int idx) {
        return lower_bound(idx);
    }

    // size(): returns total number of elements
    int size() {
        return b[n];
    }
} ;
