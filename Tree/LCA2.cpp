// faster than first
const int N = 2e5 + 7;
const int LOG = 30;
 
vector<int> adj[N];
 
int anc[N][LOG];
int level[N];
int dist[N];
vector<int> paint;
int SQ;
void DFS(int u, int p, int h) { // DFS(1 , 0 , 1 )
    level[u] = h;
    for (int &v: adj[u])
        if (p != v) {
            anc[v][0] = u;
            for (int msk = 1; (1 << msk) <= level[u] + 1; ++msk)
                anc[v][msk] = anc[anc[v][msk - 1]][msk - 1];
            DFS(v, u, h + 1);
        }
}
 
int LCA(int u, int v) {
    if (level[u] < level[v]) swap(u, v);
    for (int diff = level[u] - level[v], i = 0; diff; diff >>= 1, ++i)
        if (diff & 1)
            u = anc[u][i];
    if (u == v)return u;
    for (int i = 20; ~i; i--)
        if (anc[u][i] and anc[u][i] != anc[v][i])
            u = anc[u][i], v = anc[v][i];
    return anc[u][0];
}
 
int get_dist(int u , int v) {
    int lca = LCA(u , v);
    return level[u] + level[v] - (2*level[lca]) ;
}

// if there testcases
/* 

for (int i = 1; i <= n; ++i) {
        adj[i].clear();
        level[i] = 0 ;
        dist[i] = OO;
        for (int j = 0; j < 30; ++j) anc[i][j] = 0;
}
*/
