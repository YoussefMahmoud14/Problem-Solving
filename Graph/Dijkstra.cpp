void solve() {

    int n , m ; cin >> n >> m  ;
    vector<vector<pair<int,int>>> adj(n+3) ;
    for(int i=0 ; i<m ; ++i) {
        int u , v , w ; cin >> u >> v >> w ;
        adj[u].emplace_back(v,w) ;
        adj[v].emplace_back(u,w) ;
    }
    int s , e ; cin >> s >> e ;
    vector<int> dist(n+2,OO) ;
    priority_queue<pair<int,int> , vector<pair<int,int>> , greater<> > pq ;
    pq.push({0,s}) ;
    dist[s] = 0 ;
    int ans=0 ;

    while(!pq.empty()) {
        auto [d,u] = pq.top() ; pq.pop() ;
        if(d > dist[u]) continue ;

        // if(u == e) break ;

        for(auto [v,w] : adj[u]) {
            if(w + dist[u] < dist[v]) {
                dist[v] = dist[u]+w ;
                pq.push({ dist[v], v}) ;
            }
        }
    }



}
