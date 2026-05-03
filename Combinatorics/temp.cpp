 //dont forget to init == > init(2e6+5 , 1e9+7) ;  or init(2e6+5 , 1e9+7) ;
namespace combinatorics {

    using ll = long long;

    ll MOD;
    vector<ll> fac, inv, finv;

    // Fast Power (b^n % MOD)
    ll power(ll b, ll n) {
        b %= MOD;
        ll s = 1;
        while (n) {
            if (n & 1) s = s * b % MOD;
            b = b * b % MOD;
            n >>= 1;
        }
        return s;
    }

    // Initialize factorials & inverses up to n
    void init(int n, ll mod) {
        MOD = mod;
        fac.assign(n + 1, 0);
        inv.assign(n + 1, 0);
        finv.assign(n + 1, 0);

        fac[0] = finv[0] = 1;
        if (n >= 1) {
            fac[1] = inv[1] = finv[1] = 1;
        }

        for (int i = 1; i <= n; i++)
            fac[i] = fac[i - 1] * i % MOD;

        for (int i = 2; i <= n; i++)
            inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;

        for (int i = 2; i <= n; i++)
            finv[i] = finv[i - 1] * inv[i] % MOD;
    }

    // nCr
    ll nCr(ll n, ll r) {
        if (r < 0 || r > n) return 0;
        return fac[n] * finv[r] % MOD * finv[n - r] % MOD;
    }

    // nPr
    ll nPr(ll n, ll r) {
        if (r < 0 || r > n) return 0;
        return fac[n] * finv[n - r] % MOD;
    }

    // Modular operations
    ll mul(ll a, ll b) {
        return (a % MOD) * (b % MOD) % MOD;
    }

    ll add(ll a, ll b) {
        return (a % MOD + b % MOD) % MOD;
    }

    ll sub(ll a, ll b) {
        return ((a - b) % MOD + MOD) % MOD;
    }

    ll Inv(ll x) {
        return power(x, MOD - 2);
    }

    ll divide(ll a, ll b) {
        return mul(a, Inv(b));
    }

    // Catalan Number
    ll catalan(int n) {
        return nCr(2 * n, n) * Inv(n + 1) % MOD;
    }

    // Stars and Bars
    ll StarsAndBars(ll n, ll k) {
        return nCr(n + k - 1, k - 1);
    }

}
using namespace combinatorics ;
