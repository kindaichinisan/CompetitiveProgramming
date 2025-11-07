// Count Primes


// Given an integer n, return the number of prime numbers that are strictly less than n.

// Constraints:

// 0 <= n <= 5 * 10^6

// Example 1:

// Input: n = 10
 
// Output: 4
 
// Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
// Example 2:

// Input: n = 0
 
// Output: 0

#include<bits/stdc++.h>
using namespace std;

int primeSieve(int N){
    
    int cnt=0;

    vector<bool> sieve(N, true);
    //Mark 1 and 0 as not prime
    sieve[1] = sieve[0] = false;

    //start from 3 and mark all multiples of given i (prime) as not prime
    for(int i=2; i<=N; i++){
        
        if(sieve[i]){ //if not marked as non-prime, then is prime
            cnt++;
            for(int j = i*i; j<=N; j = j + i){
                //marking j as not prime
                sieve[j] = false;
            }
        }
    }

    return cnt;
}

int countPrimes(int n){
    return primeSieve(n-1);
}