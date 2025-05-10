#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 10;
int d[maxn];
long long dp[maxn][2];
vector<pair<int, int>> g[maxn];

void dfs(int x, int p, int w=0) {
    dp[x][0] = dp[x][1] = 0;
    vector<long long> delta;
    for (auto [v, w2] : g[x]) {
        if (v == p) continue;
        dfs(v, x, w2);
        dp[x][0] += dp[v][0];
        delta.push_back(max(0ll, dp[v][1] - dp[v][0]));
    }
    delta.push_back(0);
    sort(delta.rbegin(), delta.rend());
    if (d[x] != 0) {
        for (int i=0; i<d[x]-1; ++i)
            dp[x][0] += delta[i];

        dp[x][1] = dp[x][0] + max(0, w);
        dp[x][0] = dp[x][0] + delta[d[x]-1];
    }
}



int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    for (int i=0; i<n; ++i) cin>>d[i+1];
    for (int i=0; i<n-1; ++i) {
        int u, v, w;
        cin>>u>>v>>w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    dfs(1, 0);
    cout << dp[1][0] << '\n';
    return 0;
}