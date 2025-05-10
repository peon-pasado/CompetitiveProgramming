#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int maxn = 1e5 + 10;
vector<pair<int, int>> g[maxn];
ll dist[4][maxn];
int n, m, s, t, u, v;

void dijkstra(int src, ll dist[]) {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    for (int i=1; i<=n; ++i) dist[i] = 1e18;
    dist[src] = 0;
    q.push({0ll, src});
    while (!q.empty()) {
        auto [dv, v] = q.top(); q.pop();
        if (dv != dist[v]) continue; 
        for (auto [u, w] : g[v]) {
            if (dv + w < dist[u]) {
                dist[u] = dv + w;
                q.push({dist[u], u});
            }
        }
    }
}

vector<int> dag[maxn];
ll dp[maxn][4];
bool vis[maxn][4];
ll dfs(int x, int r) {
    if (x == t) {
        if (r == 0) return dist[2][t] + dist[3][t];
        if (r == 1) return dist[3][t];
        if (r == 2) return dist[2][t];
        if (r == 3) return 0;
    }
    if (vis[x][r]) return dp[x][r];
    vis[x][r] = 1;
    ll& ans = dp[x][r] = 1e18;
    for (auto y : dag[x]) {
        
        if (r == 0) {
            ans = min(ans, dfs(y, 0));
            ans = min(ans, dfs(y, 1) + dist[2][x]);
            ans = min(ans, dfs(y, 2) + dist[3][x]);
            ans = min(ans, dfs(y, 3) + dist[2][x] + dist[3][x]);
        } 

        if (r == 1) {
            ans = min(ans, dfs(y, 1));
            ans = min(ans, dfs(y, 3) + dist[3][x]);
        }

        if (r == 2) {
            ans = min(ans, dfs(y, 2));
            ans = min(ans, dfs(y, 3) + dist[2][x]);
        }
        
        if (r == 3) {
            ans = min(ans, dfs(y, 3));
        }
    }
    return ans;
}


int main() {
    cin>>n>>m>>s>>t>>u>>v;
    vector<tuple<int, int, int>> edges;
    for (int i=0; i<m; ++i) {
        int a, b, c;
        cin>>a>>b>>c;
        edges.push_back({a, b, c});
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    dijkstra(s, dist[0]);
    dijkstra(t, dist[1]);
    dijkstra(u, dist[2]);
    dijkstra(v, dist[3]);
    for (auto [a, b, c] : edges) {
        if (dist[0][a] + c + dist[1][b] == dist[0][t]) {
            dag[a].push_back(b);
        } 
        if (dist[0][b] + c + dist[1][a] == dist[1][s]) {
            dag[b].push_back(a);
        } 
    }
    ll ans = dist[2][v];
    ans = min(ans, dfs(s, 0));
    cout << ans << '\n';
    return 0;
}