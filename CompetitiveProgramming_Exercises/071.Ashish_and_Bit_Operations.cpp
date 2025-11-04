// Ashish and Bit Operations
// Ashish the beginner programmer has a sequence a, consisting of 2^n non-negative integers: a1, a2, ..., a2^n. Ashish is currently studying bit operations. To better understand how they work, Ashish decided to calculate some value v for a.

// Namely, it takes several iterations to calculate value v. At the first iteration, Ashish writes a new sequence a1 or a2, a3 or a4, ..., a2^n - 1 or a2^n, consisting of 2^(n - 1) elements. In other words, he writes down the bit-wise OR of adjacent elements of sequence a. At the second iteration, Ashish writes the bitwise exclusive OR of adjacent elements of the sequence obtained after the first iteration. At the third iteration Ashish writes the bitwise OR of the adjacent elements of the sequence obtained after the second iteration. And so on; the operations of bitwise exclusive OR and bitwise OR alternate. In the end, he obtains a sequence consisting of one element, and that element is v.

// Let's consider an example. Suppose that sequence a = (1, 2, 3, 4). Then let's write down all the transformations :

// (1, 2, 3, 4) → (1 or 2 = 3, 3 or 4 = 7) → (3 xor 7 = 4). The result is v = 4.

// You are given Ashish's initial sequence. But to calculate value v for a given sequence would be too easy, so you are given additional queries. Each query is a pair of integers p, b. Query p, b means that you need to perform the assignment ap = b and calculate the new value v for the new sequence a.

// Return an array containing answer for each query respectively.

// Constraints:

// 1<= n <= 17

// 1<= queries.length <= 10^5

// 1<= ai, b <= 2^30

// 1<= p <= 2^n

// Example:

// Input

// n = 2 , a =[1, 6, 3, 5]
// queries = [
//     [1, 4],
//     [3, 4],
//     [1, 2],
//     [1, 2]
// ]
// Output

// [1, 3, 3, 3]

#include<bits/stdc++.h>
using namespace std;

//
class SegmentTree{

    private:
    vector<int> st;
    int n;
    int level;
    
    //recursion
    void build(int start, int ending, int node, vector<int> &v, int level){
        // leaf node base case
        if(start==ending){
            st[node]=v[start];
            return;
        }
        int mid=(start+ending)/2;

        //left subtree is (start, mid)
        build(start, mid, 2*node+1, v, level-1);

        //right subtree is (mid+1, ending)
        build(mid+1, ending, 2*node+2, v, level-1);
        
        //build the cur node
        if(level%2==1){
            st[node]=st[node*2+1] | st[node*2+2];
        }
        else{
            st[node]=st[node*2+1] ^ st[node*2+2];
        }
    }

    void update(int start, int ending, int node, int index, int value, int level){
        //base case
        if(start==ending){
            st[node]=value;
            return;
        }

        int mid=(start+ending)/2;
        if(index<=mid){
            //left subtree
            update(start, mid, 2*node+1, index, value, level-1);
        }
        else{
            //right subtree
            update(mid+1, ending, 2*node+2, index, value, level-1);
        }

        if(level%2==1){
            st[node]=st[node*2+1] | st[node*2+2];
        }
        else{
            st[node]=st[node*2+1] ^ st[node*2+2];
        }
    }

    public:
    void init(int _n, int _level){
        this->n=_n;
        this->level = _level;
        cout<<"number of element:"<<_n<<endl;
        st.resize(4*n, 0);
    }

    void build(vector<int> &v){
        build(0, n-1, 0, v, level);
    }

    int query(){
        return st[0];
    }

    void update(int index, int value){
        update(0, n-1, 0, index, value, level);
    }

};

vector<int> solve(int n, vector<int>a, vector<vector<int>> queries){
    SegmentTree tree;
    tree.init(a.size(), n);
    tree.build(a);
    
    int q=queries.size();
    vector<int> ret;
    for(int i=0;i<q;i++){
        int idx=queries[i][0]-1;
        int vle=queries[i][1];
        tree.update(idx,vle);
        int ans=tree.query();
        ret.push_back(ans);
    }
    return ret;
}