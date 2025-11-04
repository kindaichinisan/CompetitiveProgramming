#include<bits/stdc++.h>

const int mod = 1e9 + 7;
const int sz = 2;

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