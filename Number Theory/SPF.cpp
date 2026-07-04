const int MAXA = 1e7+7 ;
int spf[MAXA];  
// time O(N log(log(N))) 
void sieve() {  
    for(int i=1;i<MAXA;i++) spf[i]=i;  
    for(int i=2;i*i<MAXA;i++){  
        if(spf[i]==i){  
            for(ll j=1LL*i*i;j<MAXA;j+=i){  
                if(spf[j]==j) spf[j]=i;  
            }  
        }  
    }  
}
