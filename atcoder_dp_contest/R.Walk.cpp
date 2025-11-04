#include <bits/stdc++.h>

using namespace std;

#define int            long long int
#define F              first
#define S              second
#define pb             push_back
#define si             set <int>
#define vi             vector <int>
#define pii            pair <int, int>
#define vpi            vector <pii>
#define vpp            vector <pair<int, pii>>
#define mii            map <int, int>
#define mpi            map <pii, int>
#define spi            set <pii>
#define endl           "\n"
#define sz(x)          ((int) x.size())
#define all(p)         p.begin(), p.end()
#define double         long double
#define que_max        priority_queue <int>
#define que_min        priority_queue <int, vi, greater<int>>
#define bug(...)       __f (#__VA_ARGS__, __VA_ARGS__)
#define print(a)       for(auto x : a) cout << x << " "; cout << endl
#define print1(a)      for(auto x : a) cout << x.F << " " << x.S << endl
#define print2(a,x,y)  for(int i = x; i < y; i++) cout<< a[i]<< " "; cout << endl
#define FOR(i, a, b)    for(int i=a;i<b;i++)

const int mod = 1e9 + 7;
const int sz = 50;

class Mat {
    public:
	int m[sz][sz];
    int n;

	Mat(int _n) {
		memset(m, 0, sizeof(m));
        n=_n;
	}
	void identity() {
		for (int i = 0; i < sz; i++) {
			m[i][i] = 1;
		}
	}
	Mat operator* (Mat a) {
		Mat res(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					res.m[i][j] += m[i][k] * a.m[k][j];
					res.m[i][j] %= mod;
				}
			}
		}
		return res;
	}

    Mat exponent(int k){
        Mat res(n);
        Mat base = *this;
        res.identity();

        while (k) {
            if (k & 1) res = res * base ;
            base = base * base ;
            k /= 2;
        }

        return res;
    }

    void printMat(){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cout<<m[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    int sumMat(){
        int sum=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                sum+=m[i][j];
            }
        }
        sum%=mod;

        return sum;
    }
};

template <typename Arg1>
void __f (const char* name, Arg1&& arg1) { cout << name << " : " << arg1 << endl; }
template <typename Arg1, typename... Args>
void __f (const char* names, Arg1&& arg1, Args&&... args) {
    const char* comma = strchr (names + 1, ',');
    cout.write (names, comma - names) << " : " << arg1 << " | ";
    __f (comma + 1, args...);
}

const int N = 200005;

void solve() {
    int N, K;
    cin >> N >> K;
    // bug(N, K);

    Mat a(N);
    // cout<<"1"<<endl;
    FOR(i,0,N){
        FOR(j,0,N){
            cin>>a.m[i][j];
        }
    }
    
    // cout<<"a"<<endl;
    // a.printMat();

    Mat b = a.exponent(K);

    // cout<<"b"<<endl;
    // b.printMat();

    cout<<b.sumMat()<<endl;
}

int32_t main() {

#ifndef ONLINE_JUDGE
    freopen("input.txt",  "r",  stdin);
    freopen("output.txt", "w", stdout);
#endif

    clock_t z = clock();

    int t = 1;
    // cin >> t;
    while (t--) solve();

    cerr << "Run Time : " << ((double)(clock() - z) / CLOCKS_PER_SEC);
    return 0;
}