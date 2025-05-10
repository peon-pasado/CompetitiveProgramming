#include <bits/stdc++.h>
using namespace std;

const int maxn = 202;
int64_t memo[maxn][maxn][62];
bool vis[maxn][maxn][62];
map<int64_t, int64_t> set_memo[maxn][maxn];
set<int64_t> set_vis[maxn][maxn]; 
int n;
int64_t m;
int64_t a[maxn];
int64_t pref_a[maxn];

void setup() {
    for (int i=1; i<=n; ++i) {
        pref_a[i] = pref_a[i - 1] + a[i - 1];
    }
}

int64_t sum(int l, int r) {
    return pref_a[r + 1] - pref_a[l];
}

//solve with range [0, m)
int64_t dp(int l, int r, int64_t m) {
    if (r - l + 1 > m + 1) return -2e18;
    if (m == 0 || r < l) return 0ll;
    int k = 63 - __builtin_clzll(m);
    if (((m+1) & m) == 0) {
        if (vis[l][r][k]) return memo[l][r][k];
    } else {
        if (set_vis[l][r].count(m)) return set_memo[l][r][m];
    }
    int64_t res = dp(l, r, (1ll << k) - 1);
    for (int i=r; i>=l; --i) {
        res = max(res, dp(l, i-1, (1ll<<k) - 1) + dp(i, r, m ^ (1ll<<k)) + sum(i, r));
    }
    if (((m+1) & m) == 0) {
        vis[l][r][k] = 1;
        memo[l][r][k] = res;
    } else {
        set_vis[l][r].insert(m);
        set_memo[l][r][m] = res;
    }
    return res;
}

int main() {
    cin>>n>>m;
    for (int i=0; i<n; ++i) {
        cin>>a[i];
    }
    setup();
    cout << dp(0, n-1, m) << '\n';
    return 0;
}