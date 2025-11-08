// Prime Sum
// You are given a number n. Find all the pairs (l, r) such that l <= r and their sum is also prime and no more than n.

// Note: l and r should be prime too.

// Constraints:

// 1 <= n <= 10^5

// Example:

// Input: n= 5
 
// Output: 1
 
// Explanation:
// In this case only pair (l, r) suits us - (2,3), because 2+3=5 , 5 is prime.

// find number of twin prime (prime that differs by 2)
#include<bits/stdc++.h>
using namespace std;

vector<bool> primeSieve(long long N){

    using ll=long long;

    vector<bool> sieve(N, true);
    //Mark 1 and 0 as not prime
    sieve[1] = sieve[0] = false;

    //start from 3 and mark all multiples of given i (prime) as not prime
    for(ll i=2; i<=N; i++){	
        if(sieve[i]){ //if not marked as non-prime, then is prime
            for(ll j = i*i; j<=N; j = j + i){
                //marking j as not prime
                sieve[j] = false;
            }
        }
    }

    return sieve;
}

//1 number must be 2.
int solve(int n){
    vector<bool> ret = primeSieve(n);
    
    int cnt=0;
    for(int i=0;i+2<ret.size();i++){
        if(ret[i] && ret[i+2]){
            cnt++;
        }
    }
    return cnt;
}