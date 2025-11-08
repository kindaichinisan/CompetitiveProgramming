class NumberTheory{

    // iterative (a>=b)
    int gcd(int a, int b) {
        while (b) {
            int t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    // recursive (a>=b)
    int gcd_recursive(int a,int b){
        if(b==0){
            return a;
        }
        return gcd_recursive(b, a%b);
    }

    // Extended Euclid's Algorithm ax + by = gcd(a,b). Find (x, y)
    vector<int> extendedGCD(int a,int b){

        if(b==0){
            //return the values of x and y 
            return {1,0,a};
        }
        vector<int> result = extendedGCD(b, a%b);

        // After recursive call is over
        int smallX = result[0];
        int smallY = result[1]; 
        int gcd  = result[2];

        int x = smallY;
        int y = smallX - (a/b)*smallY;

        return {x,y, gcd};
    }

    //Code for MMI
    int modInverse(int a,int m){

        vector<int> result = extendedGCD(a, m);
        int x = result[0];
        int gcd = result[2];

        if(gcd!=1){
            cout<<"Multiplicative Modulo Inverse doesn't exist";
            return -1;
        }

        int ans = (x%m + m)%m; //x can be negative also, {1,2,3....m-1}
        return ans;
    }


    int lcm(int a, int b) {
        return a / gcd(a, b) * b; // careful with overflow
    }

    //prime sieve: O(N*lg(lg(N)))
    // return a bool vector that is true for prime
    vector<bool> primeSieve(long long N){

        using ll=long long;

        vector<bool> sieve(N, true);
        //Mark 1 and 0 as not prime
        sieve[1] = sieve[0] = false;

        //start from 3 and mark all multiples of given i (prime) as not prime
        for(ll i=2; i<=N; i++){	
            if(sieve[i]){ //if not marked as non-prime, then is prime
                for(ll j = i*i; j<=N; j = j + i){
                    //marking j as not prime
                    sieve[j] = false;
                }
            }
        }

        return sieve;
    }

    //Brute Force O(N)
    void factorise(int n, vector<int>& prime, vector<int>& pwr){

        for(int i=2; i<=n; i++){
            if(n%i == 0){
                prime.push_back(i);
                int cnt = 0;
                while(n%i == 0){
                    cnt++;
                    n = n/i;
                }
                pwr.push_back(cnt);

                //cout<<i<<"^"<<cnt<<",";
            }
        }
    }

    //Optimised Approach
    /*
    Obs: Once N is reduced to a prime number, the 
    only factor that number will be the number itself.

    If a number doesn't have any factor till sqrt(n) 
    then it is a prime number.
    */
    // O(Sqrt(N))
    void factoriseOpt(int n, vector<int>& prime, vector<int>& pwr){

        for(int i=2; i*i<=n; i++){
            if(n%i == 0){
                prime.push_back(i);
                int cnt = 0;
                while(n%i == 0){
                    cnt++;
                    n = n/i;
                }
                pwr.push_back(cnt);

                //cout<<i<<"^"<<cnt<<",";
            }
        }

        //Out of the loop
        if(n!=1){
            prime.push_back(n);
            pwr.push_back(1);
            //cout << n <<"^"<< 1 <<endl;
        }
    }
};