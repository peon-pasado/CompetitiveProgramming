/**
 * @author Miguel Mini
 * @tag dp, number_theory, IEP, symmetry
 * @idea
 *      - we can compute the number
 *      of palindromes with minimum
 *      period equal to d:
 *
 *          f(d) = k^{(d+1)/2} - \sum_{e | d} f[e]
 *
 *      - how d is minimum period, the number
 *      of distinct rotation is d if d is odd
 *      and d/2 if d is even (for symmetry).
 *
 */

#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
int add(int a, int b) {
    return (a+b)%mod;
}

int mul(long long a, long long b) {
    return a*b%mod;
}

int ex(int a, int b) {
    int r = 1;
    while (b > 0) {
        if (b&1) r = mul(r, a);
        a = mul(a, a);
        b >>= 1;
    }
    return r;
}

const int maxn = 2010;
int f[maxn];

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> di;
    for (int i = 1; i*i <= n; ++i) {
        if (n % i == 0) {
            di.push_back(i);
            if (i*i != n) di.push_back(n/i);
        }
    }
    sort(di.begin(), di.end());
    for (int i = 0; i < di.size(); ++i) {
        f[i] = ex(k, (di[i] + 1) / 2);
        for (int j = 0; j < i; ++j) {
            if (di[i] % di[j] == 0) {
                f[i] = add(f[i], mod - f[j]);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < di.size(); ++i) {
        if (di[i] % 2 == 0) ans = add(ans, mul(di[i]/2, f[i]));
        else ans = add(ans, mul(di[i], f[i]));
    }
    cout << ans << endl;
    return 0;
}