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

#include<bits/stdc++.h>
using namespace std;

const int p = 31, mod = 1e9 + 7;

//#define int long long int

int poly_hash(vector<int> s) {
	long long hash = 0;
	long long p_power = 1;

	for (int i = 0; i < s.size(); i++) {
		hash += (s[i]+1) * p_power;
		p_power *= p;

		hash %= mod;
		p_power %= mod;
	}

	return (int)hash;
}

int powr(int a, int b) {
    // (a^b)%mod
    long long a_tmp=a;
    long long res = 1;
    while (b) {
        if (b & 1) res *= a_tmp;
        b /= 2;
        a_tmp *= a_tmp;

        a_tmp %= mod;
        res %= mod;
    }
    return (int)res;
}

int inv(int x) {
	return powr(x, mod - 2);
}

string convertVectorToString(vector<int> vec){
    string ret="";
    for(int i=0;i<vec.size();i++){
        ret+=to_string(vec[i])+",";
    }
    return ret;
}

void printMap(map<string,int> m){
    for (const auto &p : m) {
       cout << p.first << " -> " << p.second << "\n";
       
    }
}

void printVectorAndHash(vector<int> vec, int hash){
    string str=convertVectorToString(vec);
    cout<<str<<" -> "<<hash<<endl;
}

vector<int> computeHashListOfVector(vector<int> text, int len){
    vector<int> hash_list;
    map<string, int> m;
    
    //compute hash of shortest str
    vector<int> sub(text.begin(), text.begin()+ len);
    long long hash=poly_hash(sub);
    hash_list.push_back(hash);
    m[convertVectorToString(sub)]=hash;

    for (int i = 1; i + len <= text.size(); i++) {
		// remove last character
		hash = (hash - (text[i - 1] + 1) + mod) % mod;
		//cout<<text[i - 1]<<" "<<hash<<endl;

        //cout<<hash<<" "<<inv(p)<<endl;
		hash = (hash * inv(p)) % mod;
		//cout<<hash<<endl;

		hash = (hash + (text[i + len - 1] + 1) * powr(p, len - 1)) % mod;
		//cout<<text[i + len - 1]<<" "<<hash<<endl;
		
        hash_list.push_back(hash);

        vector<int> sub2(text.begin()+i, text.begin()+i+len);
        m[convertVectorToString(sub2)]=hash;
    }

    printMap(m);

    return hash_list;
}

bool checkSubVectorAgainstHashList(vector<int> text, int len, vector<int> hash_list){

    vector<int> sub(text.begin(), text.begin()+ len);
    
    long long hash=poly_hash(sub);
    
    printVectorAndHash(sub, hash);
    
    for(int k=0;k<hash_list.size();k++){
        if(hash==hash_list[k]){
            return true;
        }
    }
    
    for (int j = 1; j + len <= text.size(); j++) {
        // remove last character
        hash = (hash - (text[j - 1] + 1) + mod) % mod;

        hash = (hash * inv(p)) % mod;

        hash = (hash + (text[j + len - 1] + 1) * powr(p, len - 1)) % mod;
    
        for(int k=0;k<hash_list.size();k++){
            if(hash==hash_list[k]){
                return true;
            }
        }
    }

    return false;
}

int longestCommonSubpath(int n, vector<vector<int>> paths) {
    
    vector<int> shortest = *std::min_element(paths.begin(), paths.end(),
                                      [](const std::vector<int>& a, const std::vector<int>& b) {
                                          return a.size() < b.size();
                                      });
                                      
    int shortest_len = shortest.size();
    
    int low=0, high=shortest_len-1;
    
    int ret=0;
    while(true){
        
        if(high<low)
            break;
        
        int mid=(low+high)/2;
        
        int length = mid;
        
        vector<int> hash_list=computeHashListOfVector(shortest, length);
        
        bool all_string_common_lcs=true;
        for(int i=0;i<paths.size();i++){ //for each vector
        
            all_string_common_lcs=checkSubVectorAgainstHashList(paths[i], length, hash_list);
        
            if(!all_string_common_lcs)
                break;
            
        }
        
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