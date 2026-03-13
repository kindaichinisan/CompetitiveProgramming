// Range Set Query
// We have n colored balls, the color of the i-th ball is ci .

// you are given an array of queries where queries[i] =[li , ri] , you have to count distinct color balls in the range li to ri .

// return an array containing answer for each query respectively.

// Constraints:

// 1<= n, queries.length <= 10^5

// 1<= ci <= n

// 1<= li <= ri <= n

// Example:

// Input

// n = 5 , a =[1, 2, 1, 3]
// queries = [
//     [1, 3],
//     [2, 4],
//     [3, 3]
// ]
// Output

// [2, 3, 1]
// Explanation:

// The 1-st, 2-nd, and 3-rd balls from the left have the colors 1, 2, and 1 - two different colors.

// The 2-nd, 3-rd, and 4-th balls from the left have the colors 2, 1, and 3 - three different colors.

// The 3-rd ball from the left has the color 1- just one color.

// sort the query and process the smallest r query first
// tranverse color array from left to right.
// last keeps the last idx of the color
// fenwick tree nodes store the # unique color in node range
// if cur color is already present, remove 
#include<bits/stdc++.h>
using namespace std;

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
            x -=(x & (-x)); //last set bit
        }
        return ans;
    }

    T sum(int l, int r){
        return sum(r) - sum(l-1);
    }

    void printTree(){
        for(int i=0;i<n;i++){
            cout<<fn[i]<<" ";
        }
        cout<<endl;
    }
};

class Query{
    public:
    int l;
    int r;
    int id;
};

vector<int> solve(int n, vector<int> c, vector<vector<int>> queries){
    int m=queries.size();
    
    vector<Query> q_list;
    for(int i=0;i<m;i++){
        Query q;
        q.l=queries[i][0]-1;
        q.r=queries[i][1]-1;
        q.id=i;
        q_list.push_back(q);
    }
    sort(q_list.begin(), q_list.end(), [](Query &x, Query &y){ return x.r<y.r; });
    
    vector<int> last_color_to_idx_map(n+1,-1);
    Fenwick_Tree<int> ft; //node holds # unique color in range
    ft.init(n);
    int cur_q=0;
    vector<int> ans(m,0);
    for(int i=0;i<n;i++){
        if(last_color_to_idx_map[c[i]]!=-1){ //remove the previous from fenwick tree
            ft.add(last_color_to_idx_map[c[i]], -1);
        }
        last_color_to_idx_map[c[i]]=i;
        ft.add(i, 1);
        
        while(cur_q<m && i==q_list[cur_q].r){
            ans[q_list[cur_q].id]=ft.sum(q_list[cur_q].l, q_list[cur_q].r);
            cur_q++;
        }
    }
    
    return ans;
}