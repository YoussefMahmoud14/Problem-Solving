/// longest palendrom substring
const int B = 31 , N = 1e6+7 , mod = 2e9 + 11 ;
vector<int> pw(N) ;

void init() {
    int cur = 1 ;
    pw[0] = 1 ;
    for(int i=1 ; i<N ; ++i) {
        cur = (pw[i-1] * B )% mod ;
        cur %= mod ;
        pw[i] = cur ;
    }
}

struct Hash {

private:

    vector<int> pref , suff ;
    int sz ;
    void build_pref(string &s) {
        pref.clear() ;
        int h = 0 ;
        for(auto ch : s) {
            h = (h * B % mod + (ch - 'a' + 1)) % mod ;
            pref.emplace_back(h) ;
        }
    }

    void build_suff(string &s) {
        suff.resize(sz) ;
        int h = 0 ;
        for(int i=sz-1 ; i>=0 ; --i) {
            h = (h * B % mod + (s[i] - 'a' + 1)) % mod ;
            suff[i] = h ;
        }
    }

public:
    void init(string &s , bool suf = 1) {
        sz = s.size() ;
        build_pref(s) ;
        if(suf) build_suff(s) ;
    }
    int getPrefHash(int l , int r) {
        if(l == 0) return pref[r] ;
        int base_power = pw[r - l + 1] ;
        int ret = (pref[r] - pref[l-1] * base_power % mod + mod) % mod  ;
        return ret ;
    }
    int getSuffHash(int l,int r){
        if(r==sz-1)
            return suff[l];
        int len = r-l+1;
        return (suff[l] - suff[r+1]*pw[len]%mod + mod)%mod;
    }

    bool isPal(int l , int r) {
        return (getPrefHash(l,r) == getSuffHash(l,r)) ;
    }
};

///=====================================
void solve() {
    int n ; cin >> n ;
    string s ; cin >> s ;
    Hash h ;
    h.init(s) ;

    int ans = 1 , l = 1 , r = n/2 ;
    auto can = [&](int len) {
        int L = 0 , R = len-1 ;
        while(R < n) {
            if(h.isPal(L,R)) return 1 ;
            L++ ; R++ ;
        }
        return 0 ;
    };
    while(l <= r) {
        int mid = (l+r)/2 ;
        if(can(mid*2)) {
            l = mid+1 , ans = mid*2 ;
        }
        else r = mid-1 ;
    }
    l = 1 , r = n/2 ;
    while(l <= r) {
        int mid = (l+r)/2 ;
        if(can(mid*2 + 1)) {
            l = mid+1 , ans =  max(ans , mid*2 + 1) ;
        }
        else r = mid-1 ;
    }

    cout << ans << endl ;

}
