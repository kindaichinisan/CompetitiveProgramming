// D. Pashmak and Parmida's problem
// time limit per test3 seconds
// memory limit per test256 megabytes
// Parmida is a clever girl and she wants to participate in Olympiads this year. Of course she wants her partner to be clever too (although he's not)! Parmida has prepared the following test problem for Pashmak.

// There is a sequence a that consists of n integers a1, a2, ..., an. Let's denote f(l, r, x) the number of indices k such that: l ≤ k ≤ r and ak = x. His task is to calculate the number of pairs of indicies i, j (1 ≤ i < j ≤ n) such that f(1, i, ai) > f(j, n, aj).

// Help Pashmak with the test.

// Input
// The first line of the input contains an integer n (1 ≤ n ≤ 106). The second line contains n space-separated integers a1, a2, ..., an (1 ≤ ai ≤ 109).

// Output
// Print a single integer — the answer to the problem.
// https://codeforces.com/problemset/problem/459/D

#include<bits/stdc++.h>

using namespace std;

#define ll long long

class Fenwick_Tree{
    vector<ll> fn;
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
            idx +=(idx & (-idx)); //last set bit
        }
    }

    //simplified coding to be 1 liner
    // void add(int x, int y){
    //     for(x++;x<n;x+=(x & (-x)))  fn[x]+=y;
    // }

    //query O(log(n))
    ll sum(int x){
        x++;
        ll ans=0;
        while(x){
            ans+=fn[x];
            x -=(x & (-x)); //last set bit
        }
        return ans;
    }

    ll sum(int l, int r){
        return sum(r) - sum(l-1);
    }

    void printTree(){
        for(int i=0;i<n;i++){
            cout<<fn[i]<<" ";
        }
        cout<<endl;
    }
};

ll solve(int n, vector<int> a){
    vector<int> prefixsum(n,0);
    vector<int> suffixsum(n,0);

    unordered_map<int,int> freq; //using ordered_map results in TLE
    for(int i=0;i<n;i++){
        prefixsum[i]=++freq[a[i]];
    }

    freq.clear();
    for(int i=n-1;i>=0;i--){
        suffixsum[i]=++freq[a[i]];
    }

    Fenwick_Tree ft;
    ft.init(n);
    ll ans=0;
    for(int j=0;j<n;j++){
        ans+=ft.sum(suffixsum[j],n-1);
        ft.add(prefixsum[j]-1,1);
    }

    return ans;

}

int main(){
    int n;

    cin>>n;
    vector<int> a(n,0);

    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    ll ret = solve(n, a);

    cout<<ret<<endl;
}