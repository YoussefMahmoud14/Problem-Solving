vector<vector<int>> adj(N) ;
vector<int> dist ;
void dfs(int u,int p) {
    for(auto v:adj[u]) {
        if(v==p) continue ;
        dist[v] = dist[u]+1 ;
        dfs(v,u);

    }
}
int get_diameter(int n) {
    dist.assign(n+1, 0) ;
    dfs(1,0);
    int u = max_element(dist.begin(), dist.end()) - dist.begin() ;
    dist.assign(n+1, 0) ;
    dfs(u,0);
    int diameter = *max_element(dist.begin(), dist.end()) ;
    return diameter ;
}
