/////////////////////// Mods //////////////////////////
const int mod = 1e9+7 ; 
ll add(int x, int a) { return ((a % mod) + (x % mod)) % mod; }
ll mul(ll a, ll b) { return ((a % mod) * (b % mod)) % mod; }
ll sub(ll a, ll b) { return ((a % mod) - (b % mod) + mod) % mod; }
ll power(ll b, ll n) {
    b %= mod;
    ll s = 1;
    while (n) {
        if (n & 1) s = s * b % mod;
        b = b * b % mod;
        n >>= 1;
    }
    return s;
}

ll Inv(ll x) {
    return power(x, mod - 2);
}

ll divide(ll a, ll b) {
    return mul(a, Inv(b));
}


int id = r * m + c + 1;
int OR = 0 , XR = 0 , GCD = 0 , LCM = 1 , AND = -1 ;


//////////////////////////////////////////////////////

int _ceil(int a, int b) {
    return (a + b - 1) / b;
}

int _sqrt(int a){
    int l=0,r=5000000001;
    while(r-l>1){
        int mid=(l+r)/2;
        if(1ll*mid*mid<=a)l=mid;
        else r=mid;
    }
    return l;
} 


struct cmp {  // min heap
    bool operator()(const Node& a, const Node& b) const {
        return a.cost > b.cost;
    }
};
priority_queue<Node, vector<Node>, cmp> pq;


function<int(int,int,int)> go = [&](int m, int a, int b) -> int {
  // logic
};

/////////////////////////////////////////////////////////

int dx[8] = {-1 , 0 , 1 , 0 , -1 , 1 ,1 , -1} ,
    dy[8] = {0 , 1 , 0 , -1 , 1 , 1 , -1 , -1};

const int dx[4]={0,0,1,-1} , dy[4]={1,-1,0,0} ;

ll dx[] = {1, -1 , 0 , 0 , 0 , 0 };
ll dy[] = {0 , 0 , 1 , -1, 0 , 0 };
ll dz[] = {0 , 0 , 0 , 0 , 1, -1};

int knightx[] = {-2, -2, 2, 2, 1, 1, -1, -1};
int knighty[] = {-1, 1, -1, 1, -2, 2, -2, 2};


///////////////////////////////////////////////////////

// generate randome number
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define _rand(l, r) uniform_int_distribution<long long>(l, r)(rng)

_rand(1, 1e18); // to use 

///////////////////////////////////////////////////////

double memoryMB(long long n, long long typeSize) {
    return (double)( n * typeSize ) / ( 1024.0 * 1024.0 );
}
//  cout << "int      : " << memoryMB(n, sizeof(int)) << " MB\n"; 

