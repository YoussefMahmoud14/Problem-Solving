/// Prime factorization in O(sqrt(n))  
vector<pair<ll,ll>> primeFactorize(ll n) {  
    vector<pair<ll,ll>> arr;  
    for (ll i = 2; i * i <= n; i++) {  
        ll count = 0;  
        while (n % i == 0) {  
            n /= i;  
            count++;  
        }  
        if (count) arr.emplace_back(i, count);  
    }  
    if (n > 1) arr.emplace_back(n, 1);  
    return arr;  
} 
///////////////////////// by SPF ////////////////////////////

#define MAXN 100001 
vector<int> spf(MAXN + 1, 1); 
 
void sieve() { 
    spf[0] = 0; 
    for (int i = 2; i <= MAXN; i++) { 
        if (spf[i] == 1) { 
            for (int j = i; j <= MAXN; j += i) { 
                if (spf[j] == 1) spf[j] = i; 
            } 
        } 
    } 
} 
 
vector<int> getFactorization(int x) { 
    vector<int> ret; 
    while (x != 1) { 
        ret.push_back(spf[x]); 
        x = x / spf[x]; 
    } 
    return ret; 
} 
