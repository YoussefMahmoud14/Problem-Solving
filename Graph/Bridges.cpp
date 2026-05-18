 // build bridges and compress the graph to tree without cycle
int n , m; cin >> n >> m;

  vector<vector<pair<int,int>>> adj(n+1);
    vector<pair<int,int>> edges(m);

    for(int i=0 ; i<m ; ++i) {
        int u,v ; cin >> u >> v;
        edges[i] = {u,v};

        adj[u].push_back({v , i});
        adj[v].push_back({u , i});
    }

    vector<bool> vis(n+1);
    vector<int> low(n+1), depth(n+1);
    vector<bool> is_bridge(m , false);

    function<void(int,int)> dfs = [&](int u , int p)->void { // build bridges 
        vis[u] = true;
        low[u] = depth[u];

        for(auto [v , id] : adj[u]) {
            if(id == p) continue;

            if(vis[v]) {
                low[u] = min(low[u], depth[v]);
            }
            else {
                depth[v] = depth[u] + 1;
                dfs(v , id);

                low[u] = min(low[u], low[v]);

                if(low[v] > depth[u]) {
                    is_bridge[id] = true;
                }
            }
        }
    };

    // if graph not connected
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            depth[i]=0;
            dfs(i,-1);
        }
    }
//--------------------------   ------------------------------------
    // build components (compress graph) , each cycle represent one node
    int cur = 1;
    vector<int> ID(n+1, 0);

    function<void(int)> dfs_comp = [&](int u)->void {
        ID[u] = cur;
        for(auto [v,e] : adj[u]) {
            if(is_bridge[e] || ID[v]) continue;
            dfs_comp(v);
        }
    };

    for(int i=1 ; i<=n ; ++i) {
        if(!ID[i]) {
            dfs_comp(i);
            cur++;
        }
    }

    // build bridge tree
    tree.clear();
    tree.resize(cur); // vector<vector<int>> tree(cur) ;

    for(int i=0 ; i<m ; ++i) {
        if(is_bridge[i]) {
            auto [u , v] = edges[i];
            int cu = ID[u];
            int cv = ID[v];

            if(cu != cv) {
                tree[cu].push_back(cv);
                tree[cv].push_back(cu);
            }
        }
    }

