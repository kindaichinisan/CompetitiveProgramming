// Petya and Array
// Petya has an array a consisting of n integers. He has learned partial sums recently, and now he can calculate the sum of elements on any segment of the array really fast. The segment is a non-empty sequence of elements standing one next to another in the array.

// Now he wonders what is the number of segments in his array with the sum less than t. Help Petya to calculate this number.

// More formally, you are required to calculate the number of pairs l,r (l≤r) such that al + al+1 + ⋯ + ar−1 +ar < t .

// Return the number of segments in the Petya's array with sum of elements less than t.

// Constraints:

// 1<= n <= 10^5

// 1<= |ai| <= 10^9

// 1<= |t| <= 10^14

// Example:

// Input

// n = 5 , a =[5, -1, 3, 4, -1]
// Output

// 5
// Explanation:

// In the example, the following segments have sum less than 4:

// [2,2], sum of elements is −1

// [2,3] ,sum of elements is 2

// [3,3], sum of elements is 3

// [4,5], sum of elements is 3

// [5,5], sum of elements is −1
//codeforces https://codeforces.com/problemset/problem/1042/D

//original thought it is this soln but this soln only counts parent node if parent node sum<t.
// //wrong soln-------------------------
// #include<bits/stdc++.h>
// using namespace std;

// //summation
// class SegmentTree_Sum{

//     private:
//     vector<long long> st;
//     int n;
//     long long t;
//     long long cnt;
    
//     //recursion
//     void build(int start, int ending, int node, vector<int> &v){
//         // leaf node base case
//         if(start==ending){
//             st[node]=v[start];
//             if(st[node]<t){
//                 cnt++;
//             }
//             return;
//         }
//         int mid=(start+ending)/2;

//         //left subtree is (start, mid)
//         build(start, mid, 2*node+1, v);

//         //right subtree is (mid+1, ending)
//         build(mid+1, ending, 2*node+2, v);
        
//         //build the cur node
//         st[node]=st[node*2+1]+st[node*2+2];
        
//         if(st[node]<t)
//             cnt++;
//     }


//     public:
//     void init(int _n, long long _t){
//         this->n=_n;
//         st.resize(4*n, 0);
//         this->t=_t;
//         cnt=0;
//     }

//     void build(vector<int> &v){
//         build(0, n-1, 0, v);
//     }
    
//     long long getCnt(){
//         return cnt;
//     }

// };

// long long solve(int n,long long t, vector<int>a){
//     SegmentTree_Sum tree;
//     tree.init(a.size(), t);
//     tree.build(a);
    
//     return tree.getCnt();
// }
// //wrong soln-------------------------



#include<bits/stdc++.h>
using namespace std;

//summation
class SegmentTree_Sum{

    private:
    vector<long long> st;
    int n;
    const int default_vle=0;
    
    //recursion
    //(start, ending): cur tree range based on original vector
    //node: cur tree node idx
    //v: vector to populate to leaf node
    void build(int start, int ending, int node, vector<long long> &v){
        // leaf node base case
        if(start==ending){
            st[node]=v[start];
            return;
        }
        int mid=(start+ending)/2;

        //left subtree is (start, mid)
        build(start, mid, 2*node+1, v);

        //right subtree is (mid+1, ending)
        build(mid+1, ending, 2*node+2, v);
        
        //build the cur node
        st[node]=st[node*2+1]+st[node*2+2];
    }

    //(start, ending): cur tree range based on original vector
    //(l, r): query range
    //node: cur tree node idx
    long long query(int start, int ending, int l, int r, int node){
        //current subtree does not overlap with query range
        if(start>r || ending<l){
            return default_vle;
        }

        //current subtree is totally inside query range
        if(start>=l && ending<=r){
            return st[node];
        }

        //current subtree is partially inside query range
        int mid=(start+ending)/2;
        long long q1=query(start, mid, l, r, 2*node+1);
        long long q2=query(mid+1, ending, l, r, 2*node+2);

        return q1+q2;
    }

    //(start, ending): cur tree range based on original vector
    //node: cur tree node idx
    //(index, value): original vector index to update to new value.
    void update(int start, int ending, int node, int index, long long value){
        //base case
        if(start==ending){
            st[node]=value;
            return;
        }

        int mid=(start+ending)/2;
        if(index<=mid){
            //left subtree
            update(start, mid, 2*node+1, index, value);
        }
        else{
            //right subtree
            update(mid+1, ending, 2*node+2, index, value);
        }

        st[node] = st[node * 2 + 1] + st[node * 2 + 2];
    }

    public:
    void init(int _n){
        this->n=_n;
        st.resize(4*n, default_vle);
    }

    void build(vector<long long> &v){
        build(0, n-1, 0, v);
    }

    long long query(int l, int r){
        return query(0, n-1, l, r, 0);
    }
    void update(int index, long long value){
        update(0, n-1, 0, index, value);
    }

};

long long solve(int n,long long t, vector<int>a){
    
    
    vector<long long> ps(n+1,0LL);
    for(int i=0;i<n;i++){
        ps[i+1]=a[i]+ps[i];
    }
    
    vector<long long> combined = ps;
    for(int i=0;i<n;i++){
        combined.push_back(ps[i+1]-t);
    }
    
    sort(combined.begin(), combined.end(), greater<long long>());
    combined.erase(unique(combined.begin(), combined.end()), combined.end());
     
    map<long long, int> idx_map;
    for(int i=0;i<combined.size();i++){
        idx_map[combined[i]]=i;
    }
    
    SegmentTree_Sum tree;
    int combined_size=combined.size();
    tree.init(combined_size);
    
    long long ret=0LL;
    for(int i=0;i<=n;i++){
        //query how many previous ps is more than current ps[] - t
        long long num=ps[i]-t;
        int idx=idx_map[num];
        long long cnt=tree.query(0, idx-1);
        ret+=cnt;
        
        //update the segment tree idx by incrementing by 1
        num=ps[i];
        idx=idx_map[num];
        cnt=tree.query(idx,idx);
        tree.update(idx,cnt+1);
    }
    
    return ret;
}

int main() {

#ifndef ONLINE_JUDGE
    freopen("input.txt",  "r",  stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n;
    long long t;
    cin>>n>>t;

    vector<int>a(n,0);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    long long cnt=solve(n, t, a);

    cout<<cnt<<endl;
    return 0;
}