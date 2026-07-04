//Sieve of Eratosthenes in O(N log log N)  
vector<bool> isPrime(N, true);  
vector<int> primes ;
void sieve() {  
    isPrime[0] = isPrime[1] = false;  
    for (int i = 2; i * i < N; i++) {  
        if (isPrime[i]) { 
	        primes.push_back(i) ; 
            for (int j = i * i; j < N; j += i)  
                isPrime[j] = false;  
        }  
    }  
}
