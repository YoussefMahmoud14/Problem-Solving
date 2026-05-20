void solve(){
    vector<vector<int>> adj(n+3) ;
    vector<int> dp(n+2 , 0) ;
    int diameter = 0 ;
    function<void(int , int)> go = [&](int u , int p)->void {
        for(auto v : adj[u]) if(v != p) {
            go(v , u) ;
        }
        for(auto v : adj[u]) if(v != p) {
            dp[u] = max(dp[u] , dp[v] + 1) ;
        }
        int arr[3] = {-1,-1,-1} ;
        for(auto v : adj[u]) {
            arr[2] = dp[v] ;
            sort(arr , arr+3 , greater<int>()) ;
        }
        diameter = max(diameter , arr[0] + arr[1] + 2) ;

    };
    go(1 , -1) ;
    cout << diameter << endl ;
}
