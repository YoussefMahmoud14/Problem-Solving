/// Enumerate divisors in O(sqrt(n))  
vector<ll> divisors(ll n) {  
     vector<ll> arr;  
     for (ll i = 1; i * i <= n; i++) {  
         if (n % i == 0) {  
             arr.push_back(i);  
             if (i * i != n) arr.push_back(n / i);  
         }  
     }  
     return arr;  
 }

///////////////////////////////////////////////////////////////////

const int MAXA = 1e7+7 ;
int spf[MAXA];  
// time O(N log(log(N))) 
void sieve() {  
    for(int i=1;i<MAXA;i++) spf[i]=i;  
    for(int i=2;i*i<MAXA;i++){  
        if(spf[i]==i){  
            for(ll j=1LL*i*i;j<MAXA;j+=i){  
                if(spf[j]==j) spf[j]=i;  
            }  
        }  
    }  
}
  
// time O(log(x) + d(x)) d(x) num of divisors 
// when 1e7 max 500
vector<int> get_divisors(int x){  
    map<int,int> mp;  
    while(x>1){  
        mp[spf[x]]++;  
        x/=spf[x];  
    }  
    vector<int> divisors={1};  
    for(auto [p,c]:mp){  
        vector<int> cur;  
        ll val=1;  
        for(int i=1;i<=c;i++){  
            val*=p;  
            for(auto d:divisors)  
                cur.push_back(d*val);  
        }  
        for(auto v:cur) divisors.push_back(v);  
    }  
    return divisors;  
}
