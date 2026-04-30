const int N = 1e5+7 , LOG = 25 ;

int anc[LOG][N]; // anc[power of 2][node] = 2^i ancestor
int level[N];
vector<vector<int>> adj(N);
void build(int u , int par) {
    level[u] = level[par] + 1;
    anc[0][u] = par;

    for(int i = 1 ; i < LOG ; ++i) {
        int p = anc[i-1][u];
        anc[i][u] = anc[i-1][p];
    }

    for(auto v : adj[u]) {
        if(v != par) build(v , u);
    }
}

int Kth_anc(int u , int k) {
    for(int i = 0 ; i < LOG ; ++i) {
        if(k & (1 << i)) {
            u = anc[i][u];
        }
    }
    return u;
}

int LCA(int u , int v) {
    if(level[u] < level[v]) swap(u , v);
    u = Kth_anc(u , level[u] - level[v]);
    if(u == v) return u;

    for(int i = LOG-1 ; i >= 0 ; --i) {
        if(anc[i][u] != anc[i][v]) {
            u = anc[i][u];
            v = anc[i][v];
        }
    }

    return anc[0][u];
}

int dist(int u , int v) {
    int lca = LCA(u , v);
    return level[u] + level[v] - (2*level[lca]) ;
}
