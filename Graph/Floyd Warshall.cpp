int n , m ; cin >> n >> m ;
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, OO));
    for(int u = 1; u <= n; ++u)
        dist[u][u] = 0;

    for(int i = 0; i < m; ++i) {
        int u, v, c; cin >> u >> v >> c;
        dist[u][v] = min(dist[u][v], c);
        dist[v][u] = min(dist[v][u], c);
    }

    // 1-indexed
    for(int k = 1; k <= n; ++k)
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
