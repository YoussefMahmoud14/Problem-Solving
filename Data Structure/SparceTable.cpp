struct ST{

    vector<vector<int>> data;
    vector<int> logs;

    int merge(int &lf, int &ri) {
        return __gcd(lf, ri);
    }

    ST(vector<int> &arr) {
        int n = arr.size();
        logs.assign(n + 1, 0);

        for (int i = 2; i <= n; ++i)
            logs[i] = logs[i / 2] + 1;

        data.assign(logs[n] + 1, vector<int>(n));
        data[0] = arr;

        for (int i = 1; i <= logs[n]; ++i) {
            int l = 1 << i;
            for (int j = 0; j + l <= n; ++j) {
                data[i][j] = merge(data[i - 1][j], data[i - 1][j + (l >> 1)]);
            }
        }
    }

    int query(int l, int r) {
        int len = r - l + 1;
        int level = logs[len];
        return merge(data[level][l], data[level][r - (1 << level) + 1]);
    }
};
