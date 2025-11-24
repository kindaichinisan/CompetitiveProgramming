#include<bits/stdc++.h>
using namespace std;

// use long long so that will not overflow. 2 large number addition overflow. 2 large number multiplication more likely overflow
class ModuloOpr{

    static const int p = 1'000'000'007;
    
    //(x+y)%p = x%p + y%p. O(1)
    int addm(long long x, long long y){
        return (x + y) % p;
    }

    //(x-y)%p = (x%p - y%p + p)%p. O(1)
    int subm(long long x, long long y){
        return (x - y + p) % p;
    }

    //(x*y)%p = x%p * y%p. O(1)
    int mulm(long long x, long long y){
        return (x % p) * 1LL * (y % p) % p;
    }

    //x^y. O(log (y))
    int powm(long long x, long long y){
        long long res = 1LL;
        x %= p;
        while (y > 0) {
            if (y & 1) res = mulm(res, x);
            x = mulm(x, x);
            y >>= 1;
        }
        return res;
    }

    //O(log(p))
    int invm(long long x){
        return powm(x, p - 2);
    }

    //(x/y)%p = x%p * inv(y)%p.
    // O(log(p))
    int divm(long long x, long long y){
        return mulm(x, invm(y));
    }

    // fact[0]=0!
    // O(n)
    vector<int> calculateFactorial(int n){
        vector<int> fact(n+1,1);
        for(int i=1;i<=n, i++){
            fact[i]=mulm(fact[i-1], i);
        }
        return fact;
    }
    //nCr = n!/(r! * (n-r)!)
    // O(n + log(p))
    int ncr(int n, int r){
        if (r < 0 || r > n) return 0;
        vector<int> fact = calculateFactorial(n);
        int denom = mulm(fact[r], fact[n - r]);
        return mulm(fact[n], invm(denom));
    }
};