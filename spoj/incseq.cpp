// INCSEQ - Increasing Subsequences
// #dynamic-programming

// Given a sequence of N (1 ≤ N ≤ 10,000) integers S1, ..., SN (0 ≤ Si < 100,000), compute the number of increasing subsequences of S with length K (1 ≤ K ≤ 50 and K ≤ N); that is, the number of K-tuples i1, ..., iK such that 1 ≤ i1 < ... < iK ≤ N and Si1 < ... < SiK.

// Input
// The first line contains the two integers N and K. The following N lines contain the integers of the sequence in order.

// Output
// Print a single integer representing the number of increasing subsequences of S of length K, modulo 5,000,000.

// Example
// Input:
// 4 3
// 1
// 2
// 2
// 10

// Output:
// 2
// The two 3-tuples are (1, 2, 4) and (1, 3, 4), both corresponding to the subsequence 1, 2, 10.
// https://www.spoj.com/problems/INCSEQ/

#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define MOD 5000000
#define MAX_NUM 100000

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

long long solve(int n, int k, vector<int> seq){
    
    // cout<<n<<" "<<k<<endl;
    // for(int i=0;i<n;i++){
    //     cout<<seq[i]<<" ";
    // }
    // cout<<endl;
    vector<Fenwick_Tree<ll>> ft_list(k+1, Fenwick_Tree<ll>());
    for(int i=0;i<k;i++){
        ft_list[i].init(MAX_NUM);
    }
    for(int i=0;i<n;i++){
        // seq[i]--;
        for(int j=k-1;j>=1;j--){
            ll ways=(seq[i] > 0 ? ft_list[j-1].sum(seq[i]-1) : 0);
            ft_list[j].add(seq[i],ways);
        }
        ft_list[0].add(seq[i],1);
    }
    
    return ft_list[k-1].sum(MAX_NUM);
}

int main(){
    int n, k;
    cin>>n>>k;

    vector<int> seq(n, 0);
    for(int i=0;i<n;i++){
        cin>>seq[i];
    }
    long long ret=solve(n, k, seq);

    cout<<ret<<endl;
}