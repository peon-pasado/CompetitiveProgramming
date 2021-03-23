/**
 * @author Miguel Mini
 * @tag combinatorics, symmetry, dp
 * @idea
 *      - we can see the cube as
 *      a bipartite graph.
 *
 *      - if we fix an set in the
 *      bipartite graph (a, b, c, d)
 *      we can solve with product:
 *
 *          dp(a, b, c) * dp(a, b, d) *
 *          dp(a, c, d) * dp(b, c, d)
 *
 *      where dp(x, y, z) is number
 *      of way of fix neighbors
 *      (x, y, z) to a corner.
 *
 *      - we can divide the complexity
 *      of the last path /6 if see that
 *      contribution of tuple (a, b, c, d)
 *      is the same for every permutation.
 */
#include <bits/stdc++.h>
using namespace std;

int char_id(char c) {
    if (islower(c)) return c-'a';
    if (isupper(c)) return c-'A'+26;
    return c-'0'+52;
}

const int mod = 998244353;
int n;
int cnt[11][65][65];
int dp[65][65][65];
int rot[1<<24];
int se[5];

bool unpack(int s) {
    for (int i = 0; i < 4; ++i) {
        se[3-i] = s & 63;
        if (se[3-i] > 61) return 0;
        s >>= 6;
    }
    return 1;
}

int pack(int s[]) {
    int res = 0;
    for (int i = 0; i < 4; ++i) {
        res = (res << 6) | s[i];
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    set<string> s;
    for (int i=0; i<n; ++i) {
        string w;
        cin >> w;
        s.insert(w);
        reverse(w.begin(), w.end());
        s.insert(w);
    }
    for (auto w : s) {
        cnt[w.size()][char_id(w[0])][char_id(w.back())]++;
    }
    for (int ms = 0; ms < 1<<24; ++ms) {
        if (unpack(ms)) {
            sort(se, se+4);
            rot[pack(se)]++;
        }
    }
    int ans = 0;
    for (int i = 3; i <= 10; ++i) {
        memset(dp, 0, sizeof dp);
        for (int ms = 0; ms < 1<<24; ++ms) {
            if (!unpack(ms)) continue;
            long long prod = 1;
            for (int j = 0; j < 3; ++j) {
                prod *= cnt[i][se[j]][se[3]];
            }
            prod %= mod;
            int& r = (dp[se[0]][se[1]][se[2]] += prod);
            if (r >= mod) r -= mod;
        }
        for (int ms = 0; ms < 1<<24; ++ms) {
            if (!rot[ms]) continue;
            unpack(ms);
            long long prod = rot[ms];
            prod = prod*dp[se[0]][se[1]][se[2]]%mod;
            prod = prod*dp[se[0]][se[1]][se[3]]%mod;
            prod = prod*dp[se[0]][se[2]][se[3]]%mod;
            prod = prod*dp[se[1]][se[2]][se[3]]%mod;
            ans += prod;
            if (ans >= mod) ans -= mod;
        }
    }
    cout << ans << endl;
    return 0;
}