#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
vector<pair<int, int>> g[maxn];
int n; 
using ll = long long;
ll dp[maxn][2];

const int inf = 2e9 + 1;
vector<pair<ll, ll>> dpL[maxn];
vector<pair<ll, ll>> dpR[maxn];

pair<ll, ll> merge(pair<ll, ll> p, pair<ll, ll> q) {
    return make_pair(p.first + q.first, max(p.first + q.second, p.second + q.first));
}

void dfs(int v, int p) {
    for (auto [u, w] : g[v]) {
        if (u == p) continue;
        dfs(u, v);
    }
    int m = g[v].size();
    dpL[v].resize(m + 1);
    dpL[v][0] = make_pair(0, -inf);
    for (int i=0; i<m; ++i) {
        auto [u, w] = g[v][i];
        if (u == p) {
            dpL[v][i+1] = dpL[v][i];
        } else {
            dpL[v][i+1] = merge(dpL[v][i], make_pair(max(dp[u][0], dp[u][1] + w), dp[u][0] + w));
        }
    }
    dpR[v].resize(m + 1);
    dpR[v][m] = make_pair(0, -inf);
    for (int i=m-1; i>=0; --i) {
        auto [u, w] = g[v][i];
        if (u == p) {
            dpR[v][i] = dpR[v][i + 1];
        } else {
            dpR[v][i] = merge(dpR[v][i + 1],  make_pair(max(dp[u][0], dp[u][1] + w), dp[u][0] + w));
        }
    }
    dp[v][0] = dpL[v][m].first;
    dp[v][1] = dpL[v][m].second;
}

void dfs_reroot(int v, int p) {
    if (p > 0) {
        int m = g[v].size();
        //dpL[v].resize(m + 1);
        dpL[v][0] = make_pair(0, -inf);
        for (int i=0; i<m; ++i) {
            auto [u, w] = g[v][i];
            dpL[v][i+1] = merge(dpL[v][i],  make_pair(max(dp[u][0], dp[u][1] + w), dp[u][0] + w));
        }
        //dpR[v].resize(m + 1);
        dpR[v][m] = make_pair(0, -inf);
        for (int i=m-1; i>=0; --i) {
            auto [u, w] = g[v][i];
            dpR[v][i] = merge(dpR[v][i+1],  make_pair(max(dp[u][0], dp[u][1] + w), dp[u][0] + w));
        } 
    }
    //pair<ll, ll> po = dpL[v][m];
    for (int i=0; i<(int)g[v].size(); ++i) {
        auto [u, w] = g[v][i];
        if (u == p) continue;
        auto po = merge(dpL[v][i], dpR[v][i + 1]);
        //cout << v << ' ' << po.first << ' ' << po.second << endl;
        dp[v][0] = po.first;
        dp[v][1] = po.second;
        dfs_reroot(u, v);
    }
}


int main() {
    cin>>n;
    for (int i=0; i<n-1; ++i) {
        int a, b, c;
        cin>>a>>b>>c;
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }
    dfs(1, 0);
    dfs_reroot(1, 0);
    ll ans = -1e9;
    for (int i=1; i<=n; ++i)
        ans = max(ans, dpL[i].back().first);
    cout << ans << endl;
    return 0;
}