// binary search trick and dp digit with binary 
bool isPrime(long long n) {
    if (n == 2) return 1;
    if (n == 1 || !(n & 1)) return 0;
    for (ll i = 3; i * i <= n; i += 2) if (!(n % i)) return 0;
    return 1;
}
bitset<64> A ;
int dp[63][2][64] ; // i , upper , cnt

int go(int idx , bool upper , int cnt) {

    if(idx == -1) return (isPrime(cnt)) ;

    int &ret = dp[idx][upper][cnt] ;
    if(~ret && upper) return ret ;
    ret=0 ;
    int lim = upper ? 1 : A[idx] ;

    for(int i = 0; i<=lim ; ++i) {
        ret += go(idx - 1 , upper || (i< A[idx]) , cnt + (i==1)) ;
    }
    return ret ;
}

///=====================================
void solve() {
    int k ; cin >> k ;
    int l = 3 , r = LLONG_MAX-20 , ans = -1 ;
    while(l <= r) {
        int mid = (l+r)/2 ;
        A=mid ;
        if(go(62 , 0 , 0) >= k) r=mid-1 , ans = mid ;
        else l=mid+1 ;
    }
    cout << ans << endl ;
    
}
