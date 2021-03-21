/**
 * @author Miguel Mini
 * @tag dp, multicase
 * @idea
 *      - we can solve with dp(t)
 *      where t is length of sequence.
 *
 *      - if sequence start in 1 the
 *      contribution is dp(t-1).
 *
 *      - if sequence dont have element
 *      1 the contribution is (n-1)^2.
 *
 *      - for k < t - 1 we can use sequence:
 *
 *          "k1...1(sequence of size t - k - 1)"
 *
 *        with contribution f[t - k - 1]
 *
 *      - if k >= t-1 have contribution 1:
 *
 *          "k111111..."
 */

#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int maxn = 1e6 + 10;
int f[maxn], sf[maxn];

int main() {
    int n;
    cin >> n;
    int cua = (n - 1)*1ll*(n - 1) % mod;
    f[1] = n; sf[1] = f[1];
    f[2] = n*1ll*n % mod; sf[2] = (f[1] + f[2]) % mod;
    for (int i = 3; i <= n; ++i) {
        f[i] = f[i-1] + cua;
        if (f[i] >= mod) f[i] -= mod;
        f[i] += sf[i-3];
        if (f[i] >= mod) f[i] -= mod;
        f[i] += (n - i + 2);
        if (f[i] >= mod) f[i] -= mod;
        sf[i] = sf[i-1] + f[i];
        if (sf[i] >= mod) sf[i] -= mod;
    }
    cout << f[n] << endl;
    return 0;
}