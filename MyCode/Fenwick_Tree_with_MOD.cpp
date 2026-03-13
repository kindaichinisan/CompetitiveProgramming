#include<bits/stdc++.h>
using namespace std;

#define MOD 1000000007

template<typename T>
class Fenwick_Tree{
    vector<T> fn;
    int n;

    public:
    //eg. 0 to 8 -> 1 to 9
    //n is max vle or arr.size()-1
    void init(int n){
        this->n = n+1; //change from 0-idx to 1-idx
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