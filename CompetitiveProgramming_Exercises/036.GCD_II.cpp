// GCD II
// Frank explained to his friend Felman the algorithm of Euclides to calculate the GCD of two numbers. Then Felman implements its algorithm

// int gcd(int a, int b)
// {
// 	if (b==0)
// 		return a;
// 	else
// 		return gcd(b,a%b);
// }
// and it proposes to Frank that makes it but with a little integer and another integer that has up to 250 digits.

// Your task is to help Frank program an efficient code for the challenge of Felman.

// Constraints:

// 1 <= a <= 40000

// a <= b < 10^250

// Example:

// Input: a= 10 , b= "11"
 
// Output: 1

//https://www.spoj.com/problems/GCD2/

#include<bits/stdc++.h>
using namespace std;

int gcd_recursive(int a,int b){
    if(b==0){
        return a;
    }
    return gcd_recursive(b, a%b);
}
    
int modLargeNumber(const string &a, int b) {
    int rem = 0;
    for (char c : a) {
        rem = (rem * 10 + (c - '0')) % b;
    }
    return rem;
}

// Euclidean algorithm for GCD
int gcdLargeSmall(int a, string b) {

    int rem = modLargeNumber(b, a);
    return gcd_recursive(a, rem);
}
    
int solve(int a, string b){
    return gcdLargeSmall(a, b);
}

int main(){
    
	int t;
	cin >> t;    //Reading input from STDIN

    while(t--){
        int a;
        string b;
        cin>>a>>b;

        if(a==0){
            cout<<b<<endl;
        }
        else{
            int ans=solve(a, b);

            cout<<ans<<endl;
        }
    }
}