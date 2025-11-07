// Divisibility
// Given an array  arr, return the number of  integers between l and r, inclusive, that are divisible by at least one of the elements in arr.

// Constraints:

// 1 <= arr.length <= 18

// 1 <= arr[i] <= 10^9

// 1 <= l <= r <= 10^9

// Example:

// Input: l= 579000, r= 987654, a= [1, 2] 
 
// Output: 408655

#include<bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b; // careful with overflow
}

int numDivisible(int l,int r, vector<int> arr){
    int n=arr.size();
    
    int ret=0;
    
    for(int i=1;i<(1<<n);i++){ //for this subset. bit representation of i
        int lcm_=1;
        for(int j=0;j<n;j++){ //rightshift to check the j-th bit
            if((i>>j) & 1){
                lcm_=lcm(lcm_, arr[j]);
            }
        }
        
        //this subset has lcm l
        int temp;
        if(__builtin_popcount(i)%2){
            ret+=r/lcm_-(l-1)/lcm_;
        }
        else{
            ret-=r/lcm_-(l-1)/lcm_;
        }
    }
    
    return ret;
}