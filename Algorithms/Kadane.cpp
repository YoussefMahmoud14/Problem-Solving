ll max_sub_array_sum(vector<int> &v ,  ll n){ 
    ll maxi = 0, mx = 0; 
    for (int i = 0; i < n; i++) { 
        maxi = max(maxi + v[i], v[i]); 
        mx = max(mx, maxi); 
    } 
    return mx; 
} 
 
ll min_sub_array_sum(vector<int> &v, ll n) { 
    ll mini = OO, mn = OO; 
    for (int i = 0; i < n; i++) { 
        if (mini > 0) mini = v[i]; 
        else mini += v[i]; 
        mn = min(mn, mini); 
    } 
    return mn; 
} 
