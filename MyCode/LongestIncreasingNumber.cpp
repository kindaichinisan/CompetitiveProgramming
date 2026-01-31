#include<bits/stdc++.h>

using namespace std;

// #include "SegmentTree_Max.h"

class LongestIncreasingNumber{

    //naiive method of LIS O(N^2)
    int LIS_1(vector<int> nums){
        int n=nums.size();
        
        vector<int> dp(n,0);

        for(int i=0;i<n;i++){
            dp[i]=1; //each element can has itself with len 1
            for(int j=0;j<i;j++){
                if(nums[j]<nums[i]){
                    dp[i]=max(dp[i], dp[j]+1)
                }
            }
        }

        return *max_element(dp.begin(), dp.end()); //max element need not be at end.
    }

    //max segment tree (from small to big) + in-order update of LIS O(N*lgN) [assume no duplicate vle]
    int LIS_2a(vector<int> nums){
        int n=nums.size();
        
        vector<int> dp(n,0);

        // Pair each value with its original index
        vector<pair<int, int>> vec;
        for (int i = 0; i < nums.size(); ++i)
            vec.push_back({nums[i], i});

        // Sort by value
        sort(vec.begin(), vec.end());

        SegmentTree_Max tree;
        tree.init(n);
        for(int i=0;i<n;i++){
            int idx=vec[i].second;
            
            int max_vle=tree.query(0, idx-1);

            if(max_vle==tree.getDefault()){
                max_vle=0;
            }

            dp[idx]=max_vle+1;
            tree.update(idx, dp[idx]);
        }

        return *max_element(dp.begin(), dp.end()); //max element need not be at end.
    }

    //max segment tree (from small to big) + in-order update of LIS O(N*lgN) [has duplicate vle]
    int LIS_2b(vector<int> nums){
        int n=nums.size();
        
        vector<int> dp(n,0);

        // Pair each value with its modified index (n-original index) so that duplicate vle has the largest idx sorted first
        vector<pair<int, int>> vec;
        for (int i = 0; i < nums.size(); ++i)
            vec.push_back({nums[i], n-i});

        // Sort by value
        sort(vec.begin(), vec.end());

        SegmentTree_Max tree;
        tree.init(n);
        for(int i=0;i<n;i++){
            int idx=n-vec[i].second; //get its original index
            
            int max_vle=tree.query(0, idx-1);

            if(max_vle==tree.getDefault()){
                max_vle=0;
            }

            dp[idx]=max_vle+1;
            tree.update(idx, dp[idx]);
        }

        return *max_element(dp.begin(), dp.end()); //max element need not be at end.
    }

    //max segment tree (from left to right) + in-order update of LIS O(N*lgN) [assume no duplicate vle]
    int LIS_3a(vector<int> nums){
        int n=nums.size();
        
        vector<int> dp(n,0);

        vector<int> vec = nums;

        // Sort by value
        sort(vec.begin(), vec.end());

        map<int, int> sorted_idx;
        for (int i = 0; i < vec.size(); ++i){
            sorted_idx[vec[i]]=i;
        }

        SegmentTree_Max tree;
        tree.init(n);
        for(int i=0;i<n;i++){
            int num=nums[i];

            int idx=sorted_idx[num];
            
            int max_vle=tree.query(0, idx-1);

            if(max_vle==tree.getDefault()){
                max_vle=0;
            }

            dp[idx]=max_vle+1;
            tree.update(idx, dp[idx]);
        }

        return *max_element(dp.begin(), dp.end()); //max element need not be at end.
    }

    //max segment tree (from left to right) + in-order update of LIS O(N*lgN) [has duplicate vle]
    //not done yet. Hard to work for duplicate vles
    // int LIS_3b(vector<int> nums){
    //     int n=nums.size();
        
    //     vector<int> dp(n,0);

    //     // Pair each value with its modified index (n-original index) so that duplicate vle has the largest idx sorted first
    //     vector<pair<int, int>> vec;
    //     for (int i = 0; i < nums.size(); ++i)
    //         vec.push_back({nums[i], n-i});

    //     // Sort by value
    //     sort(vec.begin(), vec.end());

    //     map<int, int> sorted_idx;
    //     for (int i = 0; i < vec.size(); ++i){
    //         sorted_idx[vec[i]]=i;
    //     }

    //     SegmentTree_Max tree;
    //     tree.init(n);
    //     for(int i=0;i<n;i++){
    //         int num=nums[i];

    //         int idx=sorted_idx[num];
            
    //         int max_vle=tree.query(0, idx-1);

    //         if(max_vle==tree.getDefault()){
    //             max_vle=0;
    //         }

    //         dp[idx]=max_vle+1;
    //         tree.update(idx, dp[idx]);
    //     }

    //     return *max_element(dp.begin(), dp.end()); //max element need not be at end.
    // }
};