const int N=1e5+7 ;
int in[N] , out[N] , timer , n , q  ;
vector<int> color (N) ;
vector<vector<int> > adj(N) ;
void dfs(int u , int p) {
    in[u] = timer++ ;
    for(int v : adj[u]) {
        if(v == p) continue ;
        dfs(v , u) ;
    }
    out[u] = timer - 1 ;
}
