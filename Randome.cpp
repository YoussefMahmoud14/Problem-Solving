//generate randome number
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define _rand(l, r) uniform_int_distribution<long long>(l, r)(rng)

// to use --> int x = _rand(1, 1e18);

