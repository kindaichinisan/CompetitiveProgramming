#include<bits/stdc++.h>
using namespace std;

class Fenwick_Tree{
    vector<int> fn;
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
    int sum(int x){
        x++;
        int ans=0;
        while(x){
            ans+=fn[x];
            x -=(x & (-x)); //last set bit
        }
        return ans;
    }

    int sum(int l, int r){
        return sum(r) - sum(l-1);
    }

    void printTree(){
        for(int i=0;i<n;i++){
            cout<<fn[i]<<" ";
        }
        cout<<endl;
    }
};