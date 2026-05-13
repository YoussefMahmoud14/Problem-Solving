int n ; cin >> n ;
    vector<int> a(n) ;
    for(int i=0 ; i<n ; ++i) cin >> a[i] ;
    vector<int> next(n , n) , last(n , -1) ;
    stack<int> st ;
    // calc for each element a[i] next pos that grater than a[i]
    for(int i=n-1 ; i>=0 ; --i) {
        while(!st.empty() && a[i] >= a[st.top()]) st.pop() ;
        if(!st.empty()) next[i] = st.top() ;
        st.push(i) ;
    }
    while(!st.empty()) st.pop() ;
    // calc for each element a[i] last pos that grater than a[i]
    for(int i=0 ; i<n ; ++i) {
        while(!st.empty() && a[i] > a[st.top()]) st.pop() ;
        if(!st.empty()) last[i] = st.top() ;
        st.push(i) ;
    }
