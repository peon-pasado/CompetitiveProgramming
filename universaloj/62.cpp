#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

int mul(long long a, long long b) {
    return a*b%mod;
}

int ex(int a, int b) {
    int r = 1;
    while (b > 0) {
        if (b&1) r = r*1ll*a%mod;
        a = a*1ll*a%mod;
        b >>= 1;
    }
    return r;
}  

namespace nt {

    const int maxn = 1e5 + 10;
    std::bitset<maxn> composite;
    std::vector<int> prime;

    //multiplicative
    //int phi[maxn];    

    //int f[maxn]; //multiplicative function
    //int cnt[maxn]; //lamdda_p(i): exponent of p in i

    //int f_prime(int p, int k) {
    //  return ...;
    //}

    //min prime divisor
    int mu[maxn];

    void eratosthenesSieve(int n=maxn-1) {
        //phi[1]=1;
        //f[1] = 1;
        //cnt[1] = 0;
        mu[1] = 1;
        for (int i=2; i<=n; ++i) {
            if (!composite[i]) {
                prime.emplace_back(i);
                mu[i] = -1;
                //phi[i] = i-1;
                //f[i] = f_prime(i, 1);
                //cnt[i] = 1;
                //lp[i] = i;
            }
            for (int p : prime) {
                if (p * i > n) break;
                composite[p * i] = 1;
                //lp[p * i] = p;
                if (i % p == 0) { //update p * i = pˆk j with k > 1
                    mu[p * i] = 0;
                    //phi[p * i] = p * phi[i];
                    //f[p * i] = f[i] / f_prime(p, cnt[i]) * f_prime(p, cnt[i] + 1);
                    //cnt[p * i] = cnt[i] + 1;
                    break;
                } else { // minimum prime divisor de i > p
                    mu[p * i] = -mu[i];
                    //phi[p * i] = (p - 1) * phi[i];
                    //f[p * i] = f[p] * f[i];
                    //cnt[p * i] = 1;
                }
            }
        }        
    }
};



int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    nt::eratosthenesSieve();
    int n, c, d, q;
    cin>>n>>c>>d>>q;
    vector<int> b(n + 1);
    vector<int> f(n + 1), g(n + 1), gi(n + 1);
    vector<int> t(n + 1), u(n + 1), w(n + 1);
    for (int i=1; i<=n; ++i) {
        int tt = (c - d) % (mod - 1);
        if (tt < 0) tt += (mod - 1); 
        f[i] = ex(i, tt);
        g[i] = ex(i, d);
        gi[i] = ex(g[i], mod - 2);
    }
    vector<int> x(n + 1);
    while (q--) {
        for (int i=1; i<=n; ++i) {
            cin>>b[i];
        }
        for (int i=1; i<=n; ++i) {
            t[i] = u[i] = 0;
        }
        for (int d=1; d<=n; ++d) {
            for (int i=1; i * d<=n; ++i) {
                t[i * d] += mul(mod + nt::mu[i], mul(b[d], gi[d]));
                if (t[i * d] >= mod) t[i * d] -= mod;

                u[i * d] += mul(mod + nt::mu[i], f[d]);
                if (u[i * d] >= mod) u[i * d] -= mod;
            }
        }
        bool ok = 1;
        for (int i=1; i<=n; ++i) {
            if (u[i] == 0 && t[i] != 0) {
                ok = 0;
                break;
            }
            w[i] = mul(t[i], ex(u[i], mod - 2));
        }
        if (ok) {
            for (int i=n; i>=1; --i) {
                x[i] = w[i];
                for (int j=2*i; j <= n; j += i) {
                    x[i] += mod - mul(g[j], x[j]);
                    if (x[i] >= mod) x[i] -= mod;
                }
                x[i] = mul(x[i], gi[i]);
            }
            for (int i=1; i<=n; ++i) {
                cout << x[i] << " \n"[i==n];
            }
        } else {
            cout << -1 << '\n';
        }
    }

    return 0;
}