// Array Stabilization
// You are given an array of positive integers a=[ a0 , a1 , … , an−1] ( n≥2 ).

// In one step, the array a is replaced with another array of length n, in which each element is the greatest common divisor (GCD) of two neighboring elements (the element itself and its right neighbor; consider that the right neighbor of the (n−1)-th element is the 0-th element).

// Formally speaking, a new array b=[ b0 , b1 , … , bn−1]  is being built from array a=[a0 ,a1 , … , an−1] such that bi =gcd(ai,a(i+1)%n), where gcd(x,y) is the greatest common divisor of x and y, and x%y is the remainder of x dividing by y. In one step the array b is built and then the array a is replaced with b  (that is, the assignment a := b is taking place).

// For example, if a=[16,24,10,5]  then b=[gcd(16,24) , gcd(24,10) , gcd(10,5) , gcd(5,16)] =[8,2,5,1]. Thus, after one step the array a=[16,24,10,5] will be equal to [8,2,5,1].

// For a given array a, find the minimum number of steps after which all values ai become equal (that is, a0=a1=⋯=an−1). If the original array a consists of identical elements then consider the number of steps is equal to 0.

// Return minimum number of steps after which all elements of the array become equal.

// Constraints:

// 2<= n <= 10^5

// 1<= ai <= 10^6

// Example:

// Input

// n = 4 , a =[16, 24, 10, 5]
// Output
//https://codeforces.com/problemset/problem/1547/F

// 3

//sparse table implementation
// #include <bits/stdc++.h>
// using namespace std;

// int gcdop(int a, int b) {
//     return b == 0 ? a : gcdop(b, a % b);
// }

// //sparse table compute GCD for interval of 1, 2, 4, 8, 16, ...
// //st[i][j]=GCD of interval 2^i, starting at element j
// //GCD is idempotent (doing more than once is okay) => overlapping is okay
// //GCD(l=5,r=15) has interval=11 => k=3 (2^3=8 is the max power of 2 less than interval=11)
// //GCD(l=5,r=15)=GCD(st[3][5],st[3][15-8+1])=GCD(GCD(l=5,r=12), GCD(l=8,r=15)) [repeated 8:12 is okay]
// //first compute the GCD of array to find the stable vle.
// //if current array = stable vle, return 0
// //duplicate array to handle circular GCD window
// //build GCD sparse table
//binary search on minimum step k whereby all elements GCD with its right k neighbours=stable_vle
// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

// #ifndef ONLINE_JUDGE
//     freopen("input.txt",  "r",  stdin);
//     freopen("output.txt", "w", stdout);
// #endif

//     int t; 
//     cin >> t;
//     while (t--) {
//         int n;
//         cin >> n;
//         vector<int> a(n);
//         for (int i = 0; i < n; i++) cin >> a[i];

//         // global gcd
//         int g = a[0];
//         for (int i = 1; i < n; i++) g = gcdop(g, a[i]);

//         // If already all equal
//         bool same = true;
//         for (int x : a) if (x != g) same = false;
//         if (same) {
//             cout << 0 << "\n";
//             continue;
//         }

//         // Duplicate array to handle circular gcd windows
//         vector<int> b(2*n);
//         for (int i = 0; i < 2*n; i++) b[i] = a[i % n];

//         // Build sparse table for GCD-------------------
//         int LOG = 0;
//         while ((1 << LOG) <= 2*n) LOG++;

//         vector<vector<int>> st(LOG, vector<int>(2*n));
//         for (int i = 0; i < 2*n; i++) st[0][i] = b[i];
        
//         for (int j = 1; j < LOG; j++) {
//             for (int i = 0; i + (1 << j) <= 2*n; i++) {
//                 st[j][i] = gcdop(st[j-1][i], st[j-1][i + (1 << (j-1))]);
//             }
//         }
//         // Build sparse table for GCD-------------------
//         //__builtin_clz GCC implementation of count leading zeros.
//         auto range_gcd = [&](int L, int R) {
//             int len = R - L + 1;
//             int k = 31 - __builtin_clz(len); //if len=8:15, __builtin_clz=28
//             return gcdop(st[k][L], st[k][R - (1 << k) + 1]);
//         };

//         // Binary search on steps k
//         int left = 0, right = n-1, ans = n-1;
//         while (left <= right) {
//             int mid = (left + right) / 2; // candidate steps
//             bool ok = true;
//             for (int i = 0; i < n; i++) {
//                 int val = range_gcd(i, i + mid);
//                 if (val != g) {
//                     ok = false;
//                     break;
//                 }
//             }
//             if (ok) {
//                 ans = mid;
//                 right = mid - 1;
//             } else {
//                 left = mid + 1;
//             }
//         }

//         cout << ans << "\n";
//     }
//     return 0;
// }

//segment tree implementation
//longer than sparse tree implementation. O(N*lg(N)^2) vs O(N*lg(N))
#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

class SegmentTree_GCD{

    private:
    vector<int> st;
    int n;

    const int default_vle=0; //gcd(0,x)=x
    
    //recursion
    void build(int start, int ending, int node, vector<int> &v){
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
        st[node]=gcd(st[node*2+1],st[node*2+2]);
    }

    int query(int start, int ending, int l, int r, int node){
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
        int q1=query(start, mid, l, r, 2*node+1);
        int q2=query(mid+1, ending, l, r, 2*node+2);

        return gcd(q1,q2);
    }

    void update(int start, int ending, int node, int index, int value){
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

        st[node] = gcd(st[node * 2 + 1], st[node * 2 + 2]);
    }

    public:
    void init(int _n){
        this->n=_n;
        st.resize(4*n, default_vle);
    }

    void build(vector<int> &v){
        build(0, n-1, 0, v);
    }

    int query(int l, int r){
        return query(0, n-1, l, r, 0);
    }
    void update(int index, int value){
        update(0, n-1, 0, index, value);
    }

    int getDefault(){
        return default_vle;
    }

};

int solve(int n, vector<int>a){
    
    // a={16,24,10,5};
    // n=4;
    // cout<<n<<endl;
    // for(int i=0;i<n;i++){
    //     cout<<a[i]<<" ";
    // }
    // cout<<endl;
    
    // Duplicate a at the end
    a.insert(a.end(), a.begin(), a.end());
    
    int l=0;
    int r=n-1;
    int add_len;
    SegmentTree_GCD tree;
    tree.init(a.size());
    tree.build(a);
    int g=tree.query(0,n-1);
    
    int ans;
    while(l<=r){ // O(lg(N))
        add_len=(l+r)/2;
        // cout<<"l "<<l<<" "<<r<<" "<<add_len<<endl;
        bool is_stable=true;
        for(int i=0;i<n;i++){ //O(N)
            int element_g=tree.query(i,i+add_len); //O(lg(N))
            // cout<<"i "<<i<<" "<< i+add_len<<endl;
            // cout<<"g "<<element_g<<" "<<g<<endl;
            if(element_g!=g){
                is_stable=false;
                break;
            }
        }
        if(is_stable){
            r=add_len-1;
            ans=add_len;
        }
        else{
            l=add_len+1;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

#ifndef ONLINE_JUDGE
    freopen("input.txt",  "r",  stdin);
    freopen("output.txt", "w", stdout);
#endif

    int t; 
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        int ans=solve(n, a);
        cout << ans << "\n";
    }
    return 0;
}