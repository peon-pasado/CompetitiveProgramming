/**
 * @idea backtracking, prune
 * 
 *  - simule with backtracking, I assume that
 *  number of repeated nodes is at most n/2 - 1.
 * 
**/

#include <bits/stdc++.h>
using namespace std;

int e[11][11];
bool g[11][11];
int n, m;
int ans;
int vis[11];
vector<int> G[11];
const int inf = 2e9;

void dfs(int x, int mask, int sum, int t=0) {
    if (t > 4) return;
    if (sum >= ans) return;
    if (mask == ((1<<n)-1)) {
        ans = min(ans, sum);    
        return;
    }
    vis[x]++;
    for (int i=0;i<(int)G[x].size(); ++i) {
        int v = G[x][i];
        if (vis[v] < 2) {
            dfs(v, mask | (1<<v), sum + e[x][v], t+(vis[v]==1));
        }
    }
    vis[x]--;
}

bool c[11];
int dfs(int x) {
    c[x]=1;
    int ans=1;
    for (int i=0; i<n; ++i) {
        if (g[x][i]&&!c[i]) {
            ans+=dfs(i);
        }
    }
    return ans;
}

int main() {
    while (cin>>n>>m) {
        memset(g, 0, sizeof g);
        for (int i=0; i<n; ++i)
            for (int j=0; j<n; ++j)
                e[i][j] = inf;
        for (int i=0; i<n; ++i) G[i].clear();
        for (int i=0; i<m; ++i) {
            int a, b, c;
            cin>>a>>b>>c;
            a--; b--;
            g[b][a] = g[a][b] = 1;
            e[b][a] = e[a][b] = min(e[a][b], c);
        }
        for (int i=0; i<n; ++i)
            for (int j=0; j<n; ++j)
                if (g[i][j]) G[i].push_back(j);
        memset(c, 0, sizeof c);
        if (dfs(0) != n) {
            cout << -1 << '\n';
            continue;
        }
        ans = inf;
        for (int i=0; i<n; ++i) {
            dfs(i, 1<<i, 0);
        }
        if (ans == inf) cout << -1 << '\n';
        else cout << ans << '\n';
    }
    return 0;
}