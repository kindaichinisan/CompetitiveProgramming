#include<bits/stdc++.h>

using namespace std;

class Sorting{

    // assume no need for stable partition
    // partition A according to pivot, return its index after partition
    template<typename T>
    int partition(vector<T> &A, const int &A, const int &l, const int &r, const int &pivot){
        T pivot_vle=A[pivot];
        int larger_idx=l;

        swap(A[pivot], A[r]);
        for(int i=l; i<r; i++){
            if(A[i]>pivot_vle){
                swap(A[i], A[larger_idx++]);
            }
        }
        swap(A[r], A[larger_idx]);
        return larger_idx;
    }

    // assume no need for stable partition
    template <typename T>
    T find_k_th_largest(vector<T> A, const int &k){

        int l=0;
        int r=A.size()-1;

        // Create a random engine named gen and seed it with a high-quality random number from random_device
        // random_device rd;
        // default_random_engine gen(rd());
        default_random_engine gen((random_device())()); // move RNG outside loop to makes pivots more random and avoids reseeding every iteration.

        while(l<=r){
            
            //if l = 3 and r = 7:
            // Possible outputs: 3, 4, 5, 6, 7
            // Each with probability 1/5.
            uniform_int_distribution<int> dis(l, r); //generate random int in [l, r]
            int pivot_idx = dis(gen);
            
            int p=partition(A, l, r, pivot_idx);
            if(p==k-1){
                return A[p];
            }
            else if(p>k-1){
                r=p-1;
            }
            else{
                l=p+1;
            }
        }

        throw runtime_error("k is out of range");   // required to avoid undefined behavior
        
    }

    // stable partition cannot be seen in the output unless element has idx too. Just theoretical exercise.
    // Stable partition: rearranges A[l..r] around pivot while preserving relative order
    template<typename T>
    int stable_partition(vector<T> &A, const int &l, const int &r, const int &pivot) {
        T pivot_val = A[pivot];
        bool pivot_reached=false;

        vector<T> greater; // > pivot
        vector<T> smaller; // < pivot

        for (int i = l; i <= r; i++) {
            if (i == pivot){
                pivot_reached=true;
                continue; // skip pivot for now
            }
            if (A[i] > pivot_val){
                greater.push_back(A[i]);
            }
            else if (A[i] < pivot_val)
                smaller.push_back(A[i]);
            else{
                if(!pivot_reached){
                    greater.push_back(A[i]);
                }
                else{
                    smaller.push_back(A[i]);
                }
            }
        }

        // Write back into original array
        int write_idx = l;
        for (auto &x : greater) A[write_idx++] = x;

        int pivot_final_pos = write_idx;
        A[write_idx++] = pivot_val; // pivot itself

        for (auto &x : smaller) A[write_idx++] = x;

        return pivot_final_pos;
    }

};