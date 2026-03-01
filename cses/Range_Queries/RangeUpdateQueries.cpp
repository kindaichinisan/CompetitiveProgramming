// https://cses.fi/problemset/task/1651
// Range Update Queries
// Given an array of n integers, your task is to process q queries of the following types:

// increase each value in range [a,b] by u
// what is the value at position k?

// Input
// The first input line has two integers n and q: the number of values and queries.
// The second line has n integers x_1,x_2,\dots,x_n: the array values.
// Finally, there are q lines describing the queries. Each line has three integers: either "1 a b u" or "2 k".
// Output
// Print the result of each query of type 2.
// Constraints

// 1 \le n,q \le 2 \cdot 10^5
// 1 \le x_i, u \le 10^9
// 1 \le k \le n
// 1 \le a \le b \le n

// Example
// Input:
// 8 3
// 3 2 4 5 1 1 5 3
// 2 4
// 1 2 5 1
// 2 4

// Output:
// 5
// 6

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

    // int getValueAt(int x){
    //     x++;
    //     return fn[x];
    // }
    
    void printTree(){
        for(int i=0;i<n;i++){
            cout<<fn[i]<<" ";
        }
        cout<<endl;
    }

};

//this will TLE due to using Fenwick tree as Efficient point update + range sum instead of Efficient range update + point query
vector<ll> solve(int n, vector<int> nums, vector<vector<int>> queries){
    Fenwick_Tree tree;
    tree.init(nums.size());
    
    
    for(int i=0;i<n;i++){
        tree.add(i,nums[i]);
    }
    
    //tree.printTree();
    
    vector<ll> ret;
    for(int i=0;i<queries.size();i++){
        int type=queries[i][0];
        //cout<<type<<endl;
        if(type==1){
            int l=queries[i][1]-1;
            int r=queries[i][2]-1;
            int u=queries[i][3];
            for(int j=l;j<=r;j++){
                tree.add(j,u);
            }
        }
        else{
            int k=queries[i][1]-1;
            ll vle=tree.sum(k,k);
            ret.push_back(vle);
        }
        
    }
    return ret;
}

//this is okay. Efficient range update + point query
vector<ll> solve2(int n, vector<int> nums, vector<vector<int>> queries){
    Fenwick_Tree tree;
    tree.init(nums.size());
    
    vector<ll> ret;
    for(int i=0;i<queries.size();i++){
        int type=queries[i][0];
        //cout<<type<<endl;
        if(type==1){
            int l=queries[i][1]-1;
            int r=queries[i][2]-1;
            int u=queries[i][3];
            tree.add(l,u);
            if(r+1<n){
                tree.add(r+1,-u);
            }
        }
        else{
            int k=queries[i][1]-1;
            ll vle=nums[k]+tree.sum(k);
            ret.push_back(vle);
        }
        
    }
    return ret;
}

int main(){
    int n, q;
    cin>>n>>q;
    vector<int> nums(n,0);
    vector<vector<int>> queries;
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    for(int i=0;i<q;i++){
        int type;
        cin>>type;
        if(type==1){
            int l;
            int r;
            int u;
            cin>>l>>r>>u;
            queries.push_back({type,l,r,u});
        }
        else{
            int k;
            cin>>k;
            queries.push_back({type,k});  
        }
    }

    vector<ll> ret= solve2(n, nums, queries);

    for(int i=0;i<ret.size();i++){
        cout<<ret[i]<<" ";
    }
    cout<<endl;


}