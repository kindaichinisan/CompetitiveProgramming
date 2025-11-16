// Longest Common Path
// There is a country of n cities numbered from 0 to n - 1. In this country, there is a road connecting every pair of cities.

// There are m friends numbered from 0 to m - 1 who are traveling through the country. Each one of them will take a path consisting of some cities. Each path is represented by an integer array that contains the visited cities in order. The path may contain a city more than once, but the same city will not be listed consecutively.

// Given an integer n and a 2D integer array paths where paths[i] is an integer array representing the path of the ith friend, return the length of the longest common subpath that is shared by every friend's path, or 0 if there is no common subpath at all.

// A subpath of a path is a contiguous sequence of cities within that path.

// Constraints:

// 1 <= n <= 10^5

// m == paths.length

// 2 <= m <= 10^5

// sum(paths[i].length) <= 10^5

// 0 <= paths[i][j] < n

// The same city is not listed multiple times consecutively in paths[i].

// Example:

// Input: n = 5, paths = [[0,1,2,3,4],
//                        [2,3,4],
//                        [4,0,1,2,3]]
// Output: 2
 
// Explanation: The longest common subpath is [2,3].
// https://leetcode.com/problems/longest-common-subpath/

// my method is wrong as it only checks shortest len str has common hash with other string. Does not ensure that it is the same len.
// this new method checks that the same str is present in all paths.
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    #define ll long long

    ll poly_hash(vector<int> s, int mod, int p) {
        ll hash = 0;
        ll p_power = 1;

        for (int i = 0; i < s.size(); i++) {
            hash += (s[i]+1) * p_power;
            p_power *= p;

            hash %= mod;
            p_power %= mod;
        }

        return hash;
    }

    ll powr(int a, int b, int mod) {
        // (a^b)%mod
        ll a_tmp=a;
        ll res = 1;
        while (b) {
            if (b & 1) res *= a_tmp;
            b /= 2;
            a_tmp *= a_tmp;

            a_tmp %= mod;
            res %= mod;
        }
        return res;
    }

    ll inv(int x, int mod) {
        return powr(x, mod - 2, mod);
    }

    string convertVectorToString(vector<int> vec){
        string ret="";
        for(int i=0;i<vec.size();i++){
            ret+=to_string(vec[i])+",";
        }
        return ret;
    }

    void printMap(map<string,pair<ll,ll>> m){
        for (const auto &p : m) {
        cout << p.first << " -> " << p.second.first<<", "<<p.second.second << "\n";
        
        }
    }

    void printVectorAndHash(vector<int> vec, int hash){
        string str=convertVectorToString(vec);
        cout<<str<<" -> "<<hash<<endl;
    }

    //compute the hash list of substr of text of len. 
    set<pair<ll, ll>> computeHashListOfVector(vector<int> text, int len, int mod, int mod2, int p, int p2){
        set<pair<ll, ll>> hash_list;
        //map<string, pair<ll,ll>> m;
        
        //compute hash of shortest str
        vector<int> sub(text.begin(), text.begin()+ len);
        //cout<<convertVectorToString(sub)<<endl;
        ll hash=poly_hash(sub, mod, p);
        ll hash2=poly_hash(sub, mod2, p2);
        //cout<<"step 3: "<<hash2<<endl;
        hash_list.insert({hash, hash2});
        //m[convertVectorToString(sub)]={hash,hash2};

        for (int i = 1; i + len <= text.size(); i++) { //O(N)
            // remove last character
            //vector<int> sub2(text.begin()+i, text.begin()+i+len);
            //cout<<convertVectorToString(sub2)<<endl;
            hash = (hash - (text[i - 1] + 1) + mod) % mod;
            //cout<<"step 11: "<<hash<<endl;
            hash = (hash * inv(p, mod)) % mod;
            //cout<<"step 12: "<<hash<<endl;
            hash = (hash + (text[i + len - 1] + 1LL) * powr(p, len - 1, mod)) % mod;
            //cout<<"step 13: "<<hash<<endl;

            hash2 = (hash2 - (text[i - 1] + 1) + mod2) % mod2;
            //cout<<"step 21: "<<hash2<<endl;
            hash2 = (hash2 * inv(p2, mod2)) % mod2;
            //cout<<"step 22: "<<hash2<<endl;
            hash2 = (hash2 + (text[i + len - 1] + 1LL) * powr(p2, len - 1, mod2)) % mod2;
            //cout<<"step 23: "<<hash2<<endl;
            
            hash_list.insert({hash, hash2});

            //m[convertVectorToString(sub2)]={hash, hash2};
        }

        //if(len==2)
        //    printMap(m);

        return hash_list;
    }


    // Use shortest string.
    // Use binary search for best length.
    // Use rolling rabin carp to compute hash.
    // Hash must be long long becos of multiplication which may exceed int limit.
    int longestCommonSubpath(int n, vector<vector<int>> paths) {

        const int p = 31, p2=37, mod = 1e9 + 7, mod2= 1e9+9;
        
        vector<int> shortest = *std::min_element(paths.begin(), paths.end(),
                                        [](const std::vector<int>& a, const std::vector<int>& b) {
                                            return a.size() < b.size();
                                        });
                                        
        int shortest_len = shortest.size();

        //cout<<shortest_len<<endl;
        
        int low=0, high=shortest_len;
        
        int ret=0;
        while(true){ //O(log(N))
            
            if(high<low)
                break;
            
            int mid=(low+high)/2;
            
            int length = mid;

            //cout<<"length: "<<length<<endl;
            
            map<pair<ll, ll>, int> count;
            for(int i=0;i<paths.size();i++){
                set<pair<ll, ll>> hash_list=computeHashListOfVector(paths[i], length, mod, mod2, p, p2);

                for(auto &x : hash_list) count[x]++;
            }
            
            bool all_string_common_lcs=false;
            for(auto &x : count) {
                if(x.second == paths.size()){
                    all_string_common_lcs=true;
                    break;
                }
            }
            
            //cout<<length<<" "<<all_string_common_lcs<<endl;
            if(all_string_common_lcs){
                low=mid+1;
                ret=length;
            }
            else{
                high=mid-1;
            }
            
        }
        
        return ret;

    }
};