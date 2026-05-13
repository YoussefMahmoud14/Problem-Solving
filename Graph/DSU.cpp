struct DSU {
    int sz ;
    vector<int> parent , sizes  ;
    DSU(int n) {
        sz = n;
        parent = vector<int>(n+2) ;
        sizes = vector<int>(n+2) ;

        for(int i=0 ; i<=n ; ++i) parent[i] = i ,sizes[i] = 1  ;
    }
    int find(int u) {
        if(parent[u] == u) return u ;
        return parent[u] = find(parent[u]) ;
    }
    bool Merge(int u , int v) { // put small in large
        int root_u = find(u) , root_v = find(v) ;
        if(root_u == root_v) return false ;
        // u is small  ,  v is big , put u in v
        if(sizes[root_u] > sizes[root_v]) swap(root_u, root_v) ;
        sizes[root_v] += sizes[root_u] ;
        parent[root_u] = root_v ;


        return 1 ;
    }

    bool same_set(int u , int v) {
        return find(u) == find(v) ;
    }
    int get_size(int u) {
        return sizes[find(u)] ;
    }

};
