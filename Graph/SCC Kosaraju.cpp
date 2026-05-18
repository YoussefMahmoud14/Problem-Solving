// SCC Kosaraju
int n , m ; cin >> n >> m;
vector<vector<int>> adj(n+1), rev(n+1);

for(int i=0 ; i<m ; ++i) {
    int u , v ; cin >> u >> v ;
    adj[u].push_back(v);
    rev[v].push_back(u);
}

vector<int> comp;
vector<bool> vis(n+1);

function<void(int, vector<vector<int>>&)> dfs = [&](int u, vector<vector<int>>& g) {
    vis[u] = 1;
    for(auto v : g[u]) {
        if(!vis[v]) dfs(v, g);
    }
    comp.push_back(u);
};

// first dfs
for(int i=1 ; i<=n ; ++i) {
    if(!vis[i]) dfs(i , adj);
}

// reverse order
reverse(comp.begin(), comp.end());
auto order = comp;

// second dfs
fill(vis.begin(), vis.end(), 0);

vector<int> ID(n+1);
int id = 0;

for(auto u : order) {
    if(!vis[u]) {
        comp.clear();
        dfs(u , rev);

        for(auto v : comp) ID[v] = id;
        id++;
    }
}

// build DAG
vector<vector<int>> dag(id);
for(int u=1 ; u<=n ; ++u) {
    for(auto v : adj[u]) {
        if(ID[u] != ID[v]) {
            dag[ID[u]].push_back(ID[v]);
        }
    }
}
