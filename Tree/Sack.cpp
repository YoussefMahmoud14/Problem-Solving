/*
 * Sack / DSU on Tree
 *
 * 1) If we have a node U, we divide its children into two parts:
 *
 *     1- Heavy child: The child with the largest subtree size.
 *     2- Light children: The remaining children.
 *
 * 2) We maintain a data structure (DS)
 *    that stores information such as: frequencies , distinct values , sums , etc...
 *
 *--------------------- in dfs (Sack) ------------------------
 * 3) First, process all light children
 *    and REMOVE their contribution from the DS.
 * 4) Then process the heavy child
 *     and DO NOT remove its contribution.
 *
 * 5) Add the data of all light subtrees into the DS again.
 * 6) Add the data of the current node U.
 * 7) Now the DS contains all information about subtree(U).
 * 8) Answer the query for node U.
 *
 * 9) If keep == false,
 *    remove the whole subtree contribution
 *    from the DS.
 *
 * Complexity: O(N log N * time add to DS )
 */

const int N = 2e5+7 ;
int heavy[N] , SZ[N] , color[N] , ans[N] ;
int freq[N] , sum[N] , mx_freq  ;
vector<vector<int>> adj(N) ;
vector<pair<int,int>> Q[N] ;
void get_heavy(int u , int p) {
    SZ[u] = 1;
    for(auto v : adj[u]) if(v!=p) {
        get_heavy(v , u) ;
        SZ[u] += SZ[v] ;
        if(heavy[u] == 0 || SZ[v] > SZ[heavy[u]]) {
            heavy[u] = v ;
        }
    }
}

void update(int col , int delta) {

    // process

}

void Add(int u , int p , int delta) {
    update(color[u] , delta) ;
    for(auto v : adj[u]) if(v!=p) {
        Add(v , u , delta) ;
    }
}

void sack(int u , int p , bool isHeavy) { // keep = 1 if this node is the heavy

    for(auto v : adj[u]){
        if(v!=p && v != heavy[u]) {
            sack(v ,u , 0) ;
        }
    }
    if(heavy[u] != 0) {
        sack(heavy[u] , u , 1) ;
    }

    update(color[u] , 1) ; // add cur node

    for(auto v : adj[u]) { // Add in DS
        if(v!=p && v != heavy[u]) {
            Add(v ,u , +1) ;
        }
    }

    // answer query
    for(auto [x , idx] : Q[u]) {
        // ans[idx] = result ;
    }

    // remove from DS
    if(isHeavy == 0) { // not heavy
        Add(u,p , -1) ;
    }

}

///=====================================

void solve() {

    int n , q ; cin >> n >> q;
    for(int i=1 ; i<=n ; ++i) cin >> color[i] ;
    for(int i=1 ; i<n ; ++i) {
        int u , v ; cin >> u >> v ;
        adj[u].emplace_back(v) ;adj[v].emplace_back(u) ;
    }
    get_heavy(1 , 1) ;
    for(int i=0 ; i<q ; ++i) {
        int u , x ; cin >> u >> x ;
        Q[u].emplace_back(x , i+1) ;
    }
    sack(1,1,0) ;
    for(int i=1 ; i<=n ; ++i) cout << ans[i] << ' ' ;
    
}
