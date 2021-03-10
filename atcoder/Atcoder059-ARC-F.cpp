/**
 * @author Miguel Mini
 * @tag dp, symmetry
 * @idea
 *      - Note that the answer
 *      is valid for every m
 *      length word.
 *
 *      - Compute:
 *
 *          dp(used keys, current length)
 *             = 2 * dp(used keys + 1, current length + 1)
 *              + dp(used keys + 1, max(current length - 1, 0))
 *
 * @complexity O(n |s|)
 */

#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int maxn = 5010;
bool vis[maxn][maxn];
int memo[maxn][maxn];
int n, m;
string s;

int mul(long long a, long long b) {
    return a * b % mod;
}

int qpow(int a, int b) {
    int r = 1;
    while (b > 0) {
        if (b&1) r = mul(r, a);
        a = mul(a, a);
        b >>= 1;
    }
    return r;
}

int dp(int pos, int k) {
    if (pos == n) return k == m;
    if (vis[pos][k]) return memo[pos][k];
    vis[pos][k] = 1;
    int& ans = memo[pos][k] = 0;
    ans = dp(pos+1, k+1) * 2;
    if (ans >= mod) ans -= mod;
    ans += dp(pos+1, max(0, k-1));
    if (ans >= mod) ans -= mod;
    return ans;
}


int main() {
    cin >> n >> s;
    m = s.size();
    cout << mul(dp(0, 0), qpow((mod+1)/2, m)) << endl;
    return 0;
}