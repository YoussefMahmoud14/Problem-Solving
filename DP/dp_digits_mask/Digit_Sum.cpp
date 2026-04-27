// Given the numbers a and b, calculate the digit sum of [a, b].
// author:  -Abosalem-
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define ll long long
#define all(v) v.begin(),v.end()
using namespace std;
const int OO = 1e15+9;
const int limit = 1e18,  N = 21 , mod=1e9+7;

///==========================================

string L , R ;
int n ;
int dp1[20][2][2] ;
int count(int idx , int upper , int lower ) {
    if(idx == n) return 1;


    int &ret = dp1[idx][upper][lower] ;
    if(~ret && upper && lower) return ret ; // upper && lower --> tric to avoid memeset in each test case
    ret=0 ;

    int lo = lower ? 0 : L[idx]-'0' ;
    int up = upper ? 9 : R[idx]-'0' ;
    for(int i=lo ; i<= up ; ++i) {
        ret += count(idx+1 , upper|| (i < R[idx]-'0' ) , lower || (i > L[idx]-'0')) ;
    }
    return ret ;

}

int dp2[20][2][2] ;
int go(int idx , int upper , int lower ) {
    if(idx == n) return 0;

    int &ret = dp2[idx][upper][lower] ;
    if(~ret && upper && lower) return ret ;
    ret=0 ;

    int lo = lower ? 0 : L[idx]-'0' ;
    int up = upper ? 9 : R[idx]-'0' ;
    for(int i=lo ; i<= up ; ++i) {
        int cnt = count(idx+1 , upper|| (i < R[idx]-'0' ) , lower || (i > L[idx]-'0')) ;
        ret += cnt*i + go(idx+1 , upper|| (i < R[idx]-'0' ) , lower || (i > L[idx]-'0')) ;
    }
    return ret ;

}

///=====================================

void solve() {

    cin >> L >> R ;

    reverse(all(L)) ;
    /// make all strings in all test cases in the same size to avoid meme
    while((int)L.size() < 17) {
        L += '0' ;
    }
    reverse(all(L)) ;


    reverse(all(R)) ;
    while((int)R.size() < 17) {
        R += '0' ;
    }
    reverse(all(R)) ;
    n = (int)R.size() ;
    cout << go(0,0,0) << endl ;

}



signed main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    // freopen("galactic.in", "r", stdin);
    int t = 1;  cin >> t;
    memset(dp1 , -1 , sizeof dp1) ;
    memset(dp2 , -1 , sizeof dp2) ;
    while (t--) {
        solve() ;
    }


    return 0;
}
