#include <bits/stdc++.h>
using namespace std;

bool vis[55][55];
int64_t memo[55][55];
int64_t c(int n, int m) {
    if (n < m) return 0;
    if (m == 0) return 1;
    if (n == 0) return 0;
    if (vis[n][m]) return memo[n][m];
    vis[n][m] = 1;
    return memo[n][m] = c(n-1, m-1) + c(n-1, m);
}

int main() {
    int n, k, s, t;
    cin>>n>>k>>s>>t;
    if ((s & t) != s) {
        cout << 0 << '\n';
        exit(0);
    }
    int id[20] = {0};
    int nn = 0;
    for (int i=0; i<18; ++i) {
        if ((~s & (1<<i)) && (t & (1 << i))) {
            id[i] = nn++;
        } else {
            id[i] = -1;
        }
    }
    vector<int> a; 
    for (int i=0; i<n; ++i) {
        int x;
        cin>>x;
        if ((x & s) == s && (x & t) == x) {
            int m = 0;
            for (int j=0; j<18; ++j) {
                if (id[j] >= 0 && (x & (1<<j))) {
                    m |= 1<<id[j];
                }
            }
            a.push_back(m);
        }
    }
    int r = a.size();
    vector<int64_t> ck(r + 1);
    for (int i=0; i<=r; ++i) {
        for (int j=1; j<=k; ++j) {
            ck[i] += c(i, j);
        }
    }
    vector<int64_t> h(1<<nn);
    vector<int64_t> g(nn + 1);
    //sea t(S) cada bit de S indica un fallo
    // luego a lo mas hay |S| fallos, 
    // ahora g(n - |S|) = sum t(S) / binom(n, n - |S|)
    // donde cada combinaciones de S
    // indica alguna combinacion de donde
    // estan el subconjunto de fallos
    // note que la formula de f contempla
    // repeticiones, tal que solo fijando 
    // los conjuntos y el conteo doble
    // esta contemplado.
    for (int z = 0; z < 1<<nn; ++z) {
        int sz = __builtin_popcount(z);
        for (int i=0; i<r; ++i) {
            auto& v = h[z & a[i]]; 
            g[sz] -= ck[v];
            v++;
            g[sz] += ck[v];
        }
        for (int i=0; i<r; ++i) {
            h[z & a[i]]--;
        }
    }
    // calculamos f (=) a partir de g(<=).
    // note que g ya esta multiplicado 
    // por la cantidad de formas de fijar
    // elementos.
    int64_t fn = 0;
    for (int i=0; i<=nn; ++i) {
        if (i & 1) fn -= g[i];
        else fn += g[i];
    }  
    cout << fn << '\n';
    return 0;
}