struct Coordination {
    vector<int> vals;
 
    void add(int x) {
        vals.push_back(x);
    }
 
    void build() {
        std::sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
    }
 
    int get(int x) {
        return (lower_bound(vals.begin(), vals.end(), x) - vals.begin()) + 1;
    }
 
    int original(int idx) {
        return vals[idx - 1];
    }
 
    int size() {
        return vals.size();
    }
};
