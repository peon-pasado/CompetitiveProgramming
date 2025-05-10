#include <bits/stdc++.h>
using namespace std;

const int maxn = 110;
const int mod = 998244353;
int t;
int n, m, k;
vector<int> g[maxn];
int memo[102][200001];
bool vis[102][200001];
int val[maxn];

int nxt(int u) {
    if (u == t-1) return 1;
    return val[u+1] - val[u];
}

int dp(int x, int st) {
    //cout << st << endl;
    if (st >= k) return 1;
    if (vis[x][st]) return memo[x][st];
    vis[x][st] = 1;
    int &ans = memo[x][st] = dp((x + 1) % t, st + nxt(x));
    for (int v : g[x]) {
        ans += dp(v, st+1);
        if (ans >= mod) ans -= mod;
    }
    return ans;
}

int main() {
    cin>>n>>m>>k;
    map<int, int> mp;
    mp[1]; mp[n];
    vector<pair<int, int>> edges;
    for (int i=0; i<m; ++i) {
        int u, v;
        cin>>u>>v;
        edges.push_back({u, v});
        mp[u]; mp[v];
    }
    t = 0;
    for (auto& e : mp) {
        //cout << e.first << endl;
        val[t] = e.first;
        e.second = t++;
    }
    for (auto [u, v] : edges) {
        u = mp[u];
        v = mp[v];
        g[u].push_back(v);
    }
    cout << dp(0, 0) << '\n';
    return 0;
}