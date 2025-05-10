#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;
const int mod = 998244353;
int f[maxn];

namespace nt {

    const int maxn = 1e6 + 10;
    bitset<maxn> composite;
    vector<int> prime;

    //multiplicative
    //int phi[maxn];    

    //min prime divisor
    //int lp[maxn];

    void sieve() {
        //phi[1]=1;
        for (int i=2; i<maxn; ++i) {
            if (!composite[i]) {
                prime.emplace_back(i);
                //phi[i] = i-1;
                //lp[i] = i;
            }
            for (int p : prime) {
                if (p * i >= maxn) break;
                composite[p * i] = 1;
                //lp[p * i] = p;
                if (i % p == 0) {
                    //phi[p * i] = p * phi[i];
                    break;
                } else {
                    //phi[p * i] = (p - 1) * phi[i];
                }
            }
        }        
    }

};

int main() {
    nt::sieve();
    int n;
    cin>>n;
    //ways for 1 tree
    f[1] = 1;
    for (int i=1; i<=n; ++i) {
        for (int j=i; j<=n; j += i) {
            f[j + 1] += f[i];
            if (f[j + 1] >= mod) f[j + 1] -= mod;
        }
    }
    for (int p : nt::prime) {
        for (int i=1; i*p<=n; ++i) {
            f[i * p] += f[i];
            if (f[i * p] >= mod) f[i * p] -= mod;   
        }
    }

/** 
    for (int i=1; i<n; ++i) {
        for (int j=i; j<n; j+=i) {
            f[j + 1] += f[i];
            if (f[j + 1] >= mod) f[j + 1] -= mod;
        }
    }**/
    //make forest
    /** 
    for (int i=n-1; i>=1; --i) {
        for (int j=2*i; j<=n; j += i) {
            f[j] += f[i];
            if (f[j] >= mod) f[j] -= mod;
        }
    }
    **/
    for (int i=1; i<=n; ++i) {
        cout << f[i] << " \n"[i==n];
    }
    return 0;
}