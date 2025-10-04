class rabin_carp_string{

    public:
    const int p = 31;
    const int mod = 1e9 + 7;

    //O(lg(b))
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

    //O(lg(mod))
    int inv(int x) {
        return powr(x, mod - 2);
    }

    void printMap(map<string,int> m){
        for (const auto &p : m) {
           cout << p.first << " -> " << p.second << "\n";
        }
    }

    //vector<int> hash
    //O(|vec.size()|)
    int poly_hash(vector<int> vec) {
        long long hash = 0;
        long long p_power = 1;

        for (int i = 0; i < vec.size(); i++) {
            hash += (vec[i]+1) * p_power;
            p_power *= p;

            hash %= mod;
            p_power %= mod;
        }

        return (int)hash;
    }

    string convertVectorToString(vector<int> vec){
        string ret="";
        for(int i=0;i<vec.size();i++){
            ret+=to_string(vec[i])+",";
        }
        return ret;
    }

    vector<int> computeHashListOfSubVector(vector<int> vec, int len){
        vector<int> hash_list;
        //map<string, int> m;
        
        //compute hash of shortest str
        vector<int> sub(vec.begin(), vec.begin()+ len);
        long long hash=poly_hash(sub); //must be long long becos of computation
        hash_list.push_back(hash);
        //m[convertVectorToString(sub)]=hash;

        for (int i = 1; i + len <= vec.size(); i++) {
    		// remove last character
    		hash = (hash - (vec[i - 1] + 1) + mod) % mod;
    
    		hash = (hash * inv(p)) % mod;
    
    		hash = (hash + (vec[i + len - 1] + 1) * powr(p, len - 1)) % mod;
    		
            hash_list.push_back(hash);

            //vector<int> sub2(vec.begin()+i, vec.begin()+i+len);
            //m[convertVectorToString(sub2)]=hash;
        }

        //printMap(m);

        return hash_list;
    }

    bool checkSubVectorAgainstHashList(vector<int> vec, int len, vector<int> hash_list){

        vector<int> sub(vec.begin(), vec.begin()+ len);
        
        long long hash=poly_hash(sub); //must be long long becos of computation
        
        for(int k=0;k<hash_list.size();k++){
            if(hash==hash_list[k]){
                return true;
            }
        }
        
        for (int j = 1; j + len <= vec.size(); j++) {
            // remove last character
            hash = (hash - (vec[j - 1] + 1) + mod) % mod;
    
            hash = (hash * inv(p)) % mod;
    
            hash = (hash + (vec[j + len - 1] + 1) * powr(p, len - 1)) % mod;
        
            for(int k=0;k<hash_list.size();k++){
                if(hash==hash_list[k]){
                    return true;
                }
            }
        }

        return false;
    }

    //find the longest common subvector of a list of vector<int>
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
};