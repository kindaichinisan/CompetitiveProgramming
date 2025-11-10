// Coprime Divisor
// You are given two positive numbers a and b. You need to find the maximum valued integer x such that:

// x divides a i.e. a % x = 0

// x and b are co-prime i.e. gcd(x, b) = 1

// Constraints:

// 2 <= a, b <= 10^9

// Example:

// Input: a= 30, b= 12
 
// Output: 5

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

int gcd_reduction(int a, int b){
        
    int g;
    do{
        g=gcd(a, b);
        a/=g;
    }while(g>1);

    return a;
}

int solve(int a,int b){
    return gcd_reduction(a, b);
}