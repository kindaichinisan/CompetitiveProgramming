// E - LEQ  / 
// Time Limit: 2 sec / Memory Limit: 1024 MiB

// Score : 
// 500 points

// Problem Statement
// Given is a sequence of N integers: 
// A=(A1,A2,…,AN).

// Find the number of (not necessarily contiguous) subsequences 
// A′=(A1′,A2′,…,Ak′) of length at least 2 that satisfy the following condition: A1′≤Ak′​.
// Since the count can be enormous, print it modulo 998244353.

// Here, two subsequences are distinguished when they originate from different sets of indices, even if they are the same as sequences.

// Constraints
// 2≤N≤3×10 
// 5
 
// 1≤Ai≤10^9
 
// All values in input are integers.
// https://atcoder.jp/contests/abc221/tasks/abc221_e

#include<bits/stdc++.h>
using namespace std;

#define MOD 998244353
#define ll long long

template<typename T>
class Fenwick_Tree{
    vector<T> fn;
    int n;

    public:
    void init(int n){
        this->n = n+1;
        fn.resize(this->n,0);
    }

    //update O(log(n))
    void add(int idx, int vle){
        idx++; //1-based index
        while(idx<n){
            fn[idx]+=vle;
            fn[idx]%=MOD;
            idx +=(idx & (-idx)); //last set bit
        }
    }

    //simplified coding to be 1 liner
    // void add(int x, int y){
    //     for(x++;x<n;x+=(x & (-x)))  fn[x]+=y;
    // }

    //query O(log(n))
    T sum(int x){
        x++;
        T ans=0;
        while(x){
            ans+=fn[x];
            ans%=MOD;
            x -=(x & (-x)); //last set bit
        }
        return ans;
    }

    T sum(int l, int r){
        return ((sum(r) - sum(l-1))%MOD+MOD)%MOD;
    }

    void printTree(){
        for(int i=0;i<n;i++){
            cout<<fn[i]<<" ";
        }
        cout<<endl;
    }
};

vector<int> coordinate_compress1(vector<int> a){
    vector<int> b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    vector<int> ret;
    for (auto &x : a){
        x = lower_bound(b.begin(), b.end(), x) - b.begin();
        ret.push_back(x);
    }
    return ret;

}

//(x*y)%p = x%p * y%p. O(1)
int mulm(long long x, long long y, int p){
    return (x % p) * 1LL * (y % p) % p;
}

//x^y. O(log (y))
int powm(long long x, long long y, int p){
    long long res = 1LL;
    x %= p;
    while (y > 0) {
        if (y & 1) res = mulm(res, x, p);
        x = mulm(x, x, p);
        y >>= 1;
    }
    return res;
}

//O(log(p))
//x^-1 = x^(p-2). p must be prime
int invm(long long x, int p){
    return powm(x, p - 2, p);
}

int solve(int n,vector<int> a){
    vector<int> rank=coordinate_compress1(a);
    
    int maxi=*max_element(rank.begin(),rank.end());
    
    Fenwick_Tree<ll> ft;
    ft.init(maxi+1);
    
    vector<ll> pow2(n),invpow2(n);
    pow2[0]=1; //1, 2, 4, ....
    invpow2[0]=1; //1, 0.5, 0.25, ...
    long long inv2=invm(2,MOD);
    for(int i=1;i<n;i++){
        pow2[i]=pow2[i-1]*2%MOD;
        invpow2[i]=invpow2[i-1]*inv2%MOD;
    }
    
    ll ans=0;
    for(int j=0;j<n;j++){
        ans=(ans+pow2[j-1]*ft.sum(rank[j]))%MOD;
        ft.add(rank[j], invpow2[j]);
    }
    return ans;
}

int main(){
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    int ret=solve(n,a);

    cout<<ret<<endl;
}