// 315. Count of Smaller Numbers After Self
// Solved
// Hard
// Topics
// premium lock icon
// Companies
// Given an integer array nums, return an integer array counts where counts[i] is the number of smaller elements to the right of nums[i].

 

// Example 1:

// Input: nums = [5,2,6,1]
// Output: [2,1,1,0]
// Explanation:
// To the right of 5 there are 2 smaller elements (2 and 1).
// To the right of 2 there is only 1 smaller element (1).
// To the right of 6 there is 1 smaller element (1).
// To the right of 1 there is 0 smaller element.
// Example 2:

// Input: nums = [-1]
// Output: [0]
// Example 3:

// Input: nums = [-1,-1]
// Output: [0,0]
 

// Constraints:

// 1 <= nums.length <= 105
// -104 <= nums[i] <= 104
// https://leetcode.com/problems/count-of-smaller-numbers-after-self/description/

class Solution {
public:
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

    vector<int> countSmaller(vector<int>& nums) {
        int n=nums.size();
    
        int mini=*min_element(nums.begin(),nums.end());
        int maxi=*max_element(nums.begin(),nums.end());
        int diff=maxi-mini;
        
        for(int i=0;i<n;i++){
            nums[i]-=mini;
        }
        
        Fenwick_Tree<int> ft;
        ft.init(diff+1);
        vector<int> ans(n,0);
        for(int i=n-1;i>=0;i--){
            ans[i]=ft.sum(0,nums[i]-1);
            ft.add(nums[i],1);
        }
        return ans;
    }
};