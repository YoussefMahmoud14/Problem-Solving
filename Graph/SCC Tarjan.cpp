
vector<vector<int>> adj;

vector<int> tin, low, inStack, comp;
stack<int> st;

int timer = 0, compID = 0;

void tarjan(int u){
    tin[u] = low[u] = timer++;
    st.push(u);
    inStack[u] = 1;
    for(auto v : adj[u]){
        if(tin[v] == -1){
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if(inStack[v]){
            low[u] = min(low[u], tin[v]);
        }
    }
    if(low[u] == tin[u]){
        while(true){
            int v = st.top();st.pop();
            inStack[v] = 0;
            comp[v] = compID;
            if(v == u) break;
        }
        compID++;
    }
}
//-----------------------------------------------------
void solve(){
   int n , m ; cin >> n >> m ;
    adj.resize(n+1) ;
    low.resize(n+1 , OO) ;
    inStack.resize(n+1 , 0) ;
    comp.resize(n+1 , -1) ;
    tin.resize(n+1 , -1) ;
    for(int i=0 ; i<m ; ++i) {
        int u , v  ; cin >> u >> v ;
        adj[u].push_back(v) ;
    }

    tarjan(1) ;
}
