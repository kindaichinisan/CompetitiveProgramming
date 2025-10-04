#include <iostream>
#include <map>
#include <string>

using namespace std;

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

    //string hash
    //O(|s|)
    int poly_hash(string s) {
        long long hash = 0;
        long long p_power = 1;

        for (int i = 0; i < s.size(); i++) {
            hash += (s[i] - 'a' + 1) * p_power;
            p_power *= p;

            hash %= mod;
            p_power %= mod;
        }

        return (int)hash;
    }

    //once a pattern is found, return.
    //O(|text|)
    bool findPatternInText(string text, string pat){
        int pat_hash = poly_hash(pat); //O(m)

        int n = text.size(), m = pat.size();

        long long text_hash = poly_hash(text.substr(0, m)); //O(m)

        if (pat_hash == text_hash) {
            return true;
        }

        for (int i = 1; i + m <= n; i++) {
            // remove last character
            text_hash = (text_hash - (text[i - 1] - 'a' + 1) + mod) % mod;

            text_hash = (text_hash * inv(p)) % mod; //O(lg(mod))

            text_hash = (text_hash + (text[i + m - 1] - 'a' + 1) * powr(p, m - 1)) % mod; //O(lg(m))

            if (text_hash == pat_hash) {
                return true;
            }
        }

        return false;
    }

    int CountPatternInText(string text, string pat){

        int cnt=0;
        int pat_hash = poly_hash(pat); //O(m)

        int n = text.size(), m = pat.size();

        long long text_hash = poly_hash(text.substr(0, m)); //O(m)

        if (pat_hash == text_hash) {
            cnt++;
        }

        for (int i = 1; i + m <= n; i++) {
            // remove last character
            text_hash = (text_hash - (text[i - 1] - 'a' + 1) + mod) % mod;

            text_hash = (text_hash * inv(p)) % mod; //O(lg(mod))

            text_hash = (text_hash + (text[i + m - 1] - 'a' + 1) * powr(p, m - 1)) % mod; //O(lg(m))

            if (text_hash == pat_hash) {
                cnt++;
            }
        }

        return cnt;
    }


};