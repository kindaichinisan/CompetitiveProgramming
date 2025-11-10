// Alice Studies Informatics
// Today in Informatics class Alice learned about GCD and LCM. Alice is very intelligent, so she solved all the tasks momentarily and now suggests you to solve one of them as well.

// We define a pair of integers (a, b) good, if GCD(a, b) = x and LCM(a, b) = y, where GCD(a, b) denotes the greatest common divisor of a and b, and   LCM(a, b) denotes the least common multiple of a and b.

// You are given two integers x and y. You are to find the number of good pairs of integers (a, b) such that l ≤ a, b ≤ r. Note that pairs (a, b) and (b, a) are considered different if a ≠ b.

// Return the count of good pairs.

// Constraints:

// 1 <= l <= r <= 10^9

// 1 <= x <= y <= 10^9

// Example 1:

// Input: l= 1, r= 12, x= 1, y= 12
 
// Output: 4
 
// Explanation: Good pairs of integers (a, b): (1, 12), (12, 1), (3, 4) and (4, 3).
// Example 2:

// Input: l= 50, r= 100, x= 3, y= 30
 
// Output: 0
 
// Explanation: There are good pairs of integers, for example, (3, 30), but none of them fits the condition l ≤ a, b ≤ r

// https://codeforces.com/problemset/problem/992/b

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

//this is slow becos num can be 10^18, sqrt(num) can be 10^9 (large). Lead to TLE
// int solve(int l,int r,int x,int y){
//     // cout<< l <<" "<<r<<" "<<x<<" "<<y<<endl;
    
//     long long num=(long long)x*y;
//     // cout<<num<<endl;
    
//     int cnt=0;
//     for(int i=sqrt(num);i>=1;i--){
        
//         if(num%i==0){
//             int a=i;
//             int b=num/i;
            
//             if((a>=l) && (a<=r) && (b>=l) && (b<=r)){
                
//                 int g=gcd(a, b);
//                 if(g==1){
//                     if(a==b)
//                         cnt++;
//                     else 
//                         cnt+=2;
//                 }
//             }
//         }
//     }
    
//     return cnt;
// }

int solve(int l,int r,int x,int y){
    if(y%x!=0){ //not possible for LCM to be non-divisible by GCD
        return 0;
    }
    else{
        int n=y/x;
        int cnt=0;
        for(int i=sqrt(n);i>=1;i--){
            
            if(n%i==0){
                int A=i;
                int B=n/i;
                int a=A*x;
                int b=B*x;
                
                if((a>=l) && (a<=r) && (b>=l) && (b<=r)){
                    
                    int g=gcd(A, B); //wrong to use gcd(a,b)
                    if(g==1){
                        if(A==B)
                            cnt++;
                        else 
                            cnt+=2;
                    }
                }
            }
        }
        
        return cnt;
    }
    
    
}

int main(){
    int l, r, x, y;
    cin>>l>>r>>x>>y;

    int ans=solve(l, r, x, y);
    cout<<ans<<endl;
}