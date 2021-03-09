/**
 * @author Miguel Mini
 * @tags math, dp
 * @idea
 *      - we can solve with polynomial
 *      approach.
 *
 *      - let be:
 *
 *          f_i(j) = \sum\limits_{x=a[i]}^{b[i]} x^j
 *
 *      - we need (\prod\limits_{i=1}^n f_i)(c)
 *      with usual multiplication.
 *
 * @complexity O(n C^2)
 */

#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int maxn = 410;
int sum[maxn][maxn];
int f[maxn][maxn];
int A[maxn], B[maxn];

int add(int a, int b) {
    return (a+b)%mod;
}

int mul(long long a, long long b) {
    return a * b % mod;
}

int main() {
    int n, C;
    cin >> n >> C;
    for (int i = 0; i < n; ++i) cin >> A[i];
    for (int i = 0; i < n; ++i) cin >> B[i];
    for (int i = 1; i < maxn; ++i) {
        int pot = 1;
        for (int j = 0; j < maxn; ++j) {
            sum[i][j] = sum[i-1][j] + pot;
            if (sum[i][j] >= mod) sum[i][j] -= mod;
            pot = pot*1ll*i%mod;
        }
    }
    for (int i = 0; i <= C; ++i) {
        for (int j = 0; j < n; ++j) {
            f[j][i] = sum[B[j]][i] - sum[A[j]-1][i];
            if (f[j][i] < 0) f[j][i] += mod;
        }
    }
    for (int i = 1; i < n; ++i) {
        int t[maxn];
        for (int j = 0; j <= C; ++j) t[j] = 0;
        for (int a = C; a >= 0; --a) {
            for (int b = 0; b <= a; ++b) {
                t[a] = add(t[a], mul(f[i][a-b], f[i-1][b]));
            }
        }
        for (int j = 0; j <= C; ++j) f[i][j] = t[j];
    }
    cout << f[n-1][C] << endl;
    return 0;
}