// Perfect Squares


// Given an integer n, return the least number of perfect square numbers that sum to n.

// A perfect square is an integer that is the square of an integer; in other words, it is the product of some integer with itself. For example, 1, 4, 9, and 16 are perfect squares while 3 and 11 are not.

// Constraints:

// 1 <= n <= 10^4

// Example :

// Input: n = 12
 
// Output: 3
 
// Explanation: 12 = 4 + 4 + 4.

//this is an O(N^2) algo. Got a O(N^1.5) algo for DP.
//Using number theory (Lagrange’s Four Square Theorem), this is O(N^0.5) algo.
#include<bits/stdc++.h>
using namespace std;

int memo[10001];

int compute(int n){
    int n_sqrt= static_cast<int>(sqrt(n));
    if(n_sqrt*n_sqrt==n){
        return 1;
    }
    
    int min_num=10000;
    for(int i=(n+1)/2;i<n;i++){
        int &ans1 = memo[i];
        if(ans1==-1){
            ans1=compute(i);
        }
        int &ans2=memo[n-i];
        if(ans2==-1){
            ans2=compute(n-i);
        }
        int ans3=ans1+ans2;
        if(ans3<min_num){
            min_num=ans3;
        }
    }
    
    return min_num;
}

int numSquares(int n) {
    
    memset(memo,-1,sizeof(memo));
    
    return compute(n);
}