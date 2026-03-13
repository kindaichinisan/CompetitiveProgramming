#include<bits/stdc++.h>
using namespace std;

//ai can be large vle
//return bi which ranges from 0 to n (rank of ai)
vector<int> coordinate_compress1(vector<int> a){
    vector<int> b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    vector<int> ret;
    for (auto &x : a){
        x = lower_bound(b.begin(), b.end(), x) - b.begin();
        ret.push_back(x);
    }
    return ret;

}