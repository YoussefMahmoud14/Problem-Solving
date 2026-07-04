// Linear Sieve to generate all prime numbers up to N in O(N) time 
// N can up to 1e7
const int N=1e5+5;
vector<bool>isPrime(N,true);
vector<int>p;
void linear_sieve(){
    isPrime[0]=isPrime[1]=0;
    for(ll i=2;i<N;i++){
        if(isPrime[i]==1) p.push_back(i);
        for(ll o=0;o<p.size();o++)
        {
            if(i * p[o] >= N) break;
            isPrime[i * p[o]] = 0;
            if(i % p[o]==0) break;
        }
    }
}
