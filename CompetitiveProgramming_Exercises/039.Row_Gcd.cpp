// Row Gcd
// You are given two positive integer sequences a1, ... ,an and b1, ... ,bm. For each j=1, ... ,m find the greatest common divisor of a1+bj, ... ,an+bj.

// return an array containing answer for each j=1,...,m respectively.

// Constraints:

// 1 <= n, m <= 2*10^5

// 1 <= ai, bj <= 10^9

// Example:

// Input: n= 4, m= 4, a= {1, 25, 121, 169}, b= {1, 2, 7, 23}
 
// Output: {2, 3, 8, 24}

// https://codeforces.com/problemset/problem/1458/a

#include<bits/stdc++.h>
using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

long long gcd(vector<long long> nums){
    long long g=0LL;
    for(int i=0;i<nums.size();i++){
        g=gcd(g, nums[i]);
    }
    return g;
}

vector<long long> solve(int n,int m, vector<long long> a, vector<long long> b){
    vector<long long> a1_diff;

    sort(a.begin(), a.end()); //so that a[0] is smallest.
    for(int i=0;i<n;i++){
        a1_diff.push_back(a[i]-a[0]);
    }
    
    long long g_a1_diff=gcd(a1_diff);
    
    vector<long long> ret;
    for(int j=0;j<m;j++){
        long long g=gcd(g_a1_diff, a[0]+b[j]);
        ret.push_back(g);
    }
    
    return ret;
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("input.txt",  "r",  stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n, m;
    cin>>n>>m;
    vector<long long> a(n,0);
    vector<long long> b(m,0);

    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    for(int j=0;j<m;j++){
        cin>>b[j];
    }

    vector<long long> ret=solve(n, m, a, b);

    for(int i=0;i<ret.size();i++){
        cout<<ret[i]<<" ";
    }
    cout<<endl;
}