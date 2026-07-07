#define pii pair<int,int>
#define F first
#define S second

struct Node {
    pii rev{}, fr{};
    int sz{};
};

const int N = 2e5 + 5;
int MOD1, MOD2, B1, B2;
pair<int, int> pw[N];

struct SegTreeHash {

private:

#define md ((lx + rx) >> 1)
#define LF (x * 2 + 1)
#define RT (x * 2 + 2)

    vector<Node> seg;
    int n;
    Node mrg(const Node &lf, const Node &rt) {
        Node res;
        res.sz = lf.sz + rt.sz;
        // Forward Hash
        res.fr = {
            (lf.fr.F * 1LL * pw[rt.sz].F % MOD1 + rt.fr.F) % MOD1,
            (lf.fr.S * 1LL * pw[rt.sz].S % MOD2 + rt.fr.S) % MOD2
        };
        // Reverse Hash
        res.rev = {
            (rt.rev.F * 1LL * pw[lf.sz].F % MOD1 + lf.rev.F) % MOD1,
            (rt.rev.S * 1LL * pw[lf.sz].S % MOD2 + lf.rev.S) % MOD2
        };
        return res;
    }

    void build(const string &s, int x, int lx, int rx) {

        if (lx == rx) {
            seg[x].fr = {s[lx] % MOD1, s[lx] % MOD2};
            seg[x].rev = {s[lx] % MOD1, s[lx] % MOD2};
            seg[x].sz = 1;
            return;
        }

        build(s, LF, lx, md);
        build(s, RT, md + 1, rx);

        seg[x] = mrg(seg[LF], seg[RT]);
    }

public:

    SegTreeHash(int n) : n(n), seg(n << 2) {}
    SegTreeHash(const string &s) : SegTreeHash(s.size()) {
        build(s, 0, 0, n - 1);
    }

    Node query(int l, int r, int x = 0, int lx = 0, int rx = -1) {
        if (rx == -1)rx = n - 1;
        // fully inside
        if (l <= lx && rx <= r) return seg[x];
        // no intersection
        if (r < lx || rx < l) return {};

        return mrg(
            query(l, r, LF, lx, md),
            query(l, r, RT, md + 1, rx)
        );
    }

    void update(int i, char v, int x = 0, int lx = 0, int rx = -1) {

        if (rx == -1) rx = n - 1;
        if (lx == rx) {
            seg[x].fr = {v % MOD1, v % MOD2};
            seg[x].rev = {v % MOD1, v % MOD2};
            seg[x].sz = 1;
            return;
        }
        if (i <= md) update(i, v, LF, lx, md);
        else update(i, v, RT, md + 1, rx);

        seg[x] = mrg(seg[LF], seg[RT]);
    }

#undef md
#undef LF
#undef RT
};

void init() {

    if (B1) return;
    random_device rd;
    mt19937 mt(rd());
    auto rnd = [&](int l, int r) {
        return uniform_int_distribution<int>(l, r)(mt);
    };

    auto check = [](int x) {
        for (int i = 2; i <= x / i; ++i) {
            if (x % i == 0) return false;
        }
        return true;
    };

    B1 = rnd(100, 500);
    B2 = rnd(100, 500);
    MOD1 = rnd(2e8, 2e9);
    MOD2 = rnd(2e8, 2e9);

    while (!check(MOD1)) MOD1--;
    while (MOD1 == MOD2 || !check(MOD2)) MOD2--;
    pw[0] = {1, 1};
    for (int i = 1; i < N; i++) {
        pw[i].F = 1LL * pw[i - 1].F * B1 % MOD1;
        pw[i].S = 1LL * pw[i - 1].S * B2 % MOD2;
    }
}

////////////////////////////////////////////////////
// update char and query that palindrom
void solve() {
    int n , q; cin >> n >> q ;
    string s ; cin >> s ;
    SegTreeHash st (s) ;
    while(q--) {
        int op ; cin >> op ;
        if(op == 1) {
            int idx ; char ch ; cin >> idx >> ch ;
            st.update(idx-1 , ch ) ;
        }
        else {
            int l , r ; cin >> l >> r ; l-- ; r-- ;
            Node ans = st.query(l,r) ;
            if(ans.fr == ans.rev) cout << "YES" << endl ;
            else cout << "NO" << endl ;
        }
    }
}
