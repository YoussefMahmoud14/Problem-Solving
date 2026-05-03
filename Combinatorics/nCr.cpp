// mods 
ll add(int x, int a) { return ((a % mod) + (x % mod)) % mod; }
ll mul(ll a, ll b) { return ((a % mod) * (b % mod)) % mod; }
ll sub(ll a, ll b) { return ((a % mod) - (b % mod) + mod) % mod; }
ll power(ll b, ll n) {
    b %= mod;
    ll s = 1;
    while (n) {
        if (n & 1) s = s * b % mod;
        b = b * b % mod;
        n >>= 1;
    }
    return s;
}

ll Inv(ll x) {
    return power(x, mod - 2);
}

ll divide(ll a, ll b) {
    return mul(a, Inv(b));
}
//-----------------------------------------------------
int fact[N], inv[N], finv[N];

void pre() {
    fact[0] = fact[1] = inv[0] = inv[1] = finv[0] = finv[1] = 1;
    for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * i % mod;
    for (int i = 2; i < N; i++) inv[i] = mod - (mod / i) * inv[mod % i] % mod;
    for (int i = 2; i < N; i++)finv[i] = finv[i - 1] * inv[i] % mod;
}

ll nCr(ll n, ll r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * finv[r] % mod * finv[n - r] % mod;
}
//----------------------------------------------------
/// when r <= 4 and no mod 
long long nCr(int n, int r) {
    if (r > n) return 0;
    int k = n - r;
    if (k > r) k = r;

    if (k == 0) return 1;
    if (k == 1) return n;
    if (k == 2) return n * (n - 1) / 2;
    if (k == 3) return n * (n - 1) * (n - 2) / 6;
    if (k == 4) return n * (n - 1) * (n - 2) * (n - 3) / 24;
    return 0;
}
