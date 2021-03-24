/**
 * @author Miguel Mini
 * @tag dfs, priority_queue, greedy
 * @idea
 *      - we can equalize the heights
 *      all the closest points with
 *      height less than a city so that
 *      they help to take higher points.
 *
 *      - after this I can greedily start
 *      covering the smallest nodes to the
 *      largest points with a simple dfs
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1010;
int a[maxn][maxn];
int b[maxn][maxn];
bool vis[maxn][maxn];
int n, m;
vector<pair<int, int>> adj[maxn];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool valid(int x, int y) {
    return x>=0 && y>=0 && x<n && y<m;
}

void dfs(int x, int y) {
    vis[x][y] = 1;
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (!valid(nx, ny)) continue;
        if (vis[nx][ny]) continue;
        if (a[x][y] <= a[nx][ny]) {
            dfs(nx, ny);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    using iii = pair<int, pair<int, int>>;
    priority_queue<iii, vector<iii>, greater<iii>> Q;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", a[i]+j);
            b[i][j] = a[i][j];
            if (a[i][j] > 0) {
                Q.push({a[i][j], {i, j}});
            }
        }
    }
    while (!Q.empty()) {
        auto q = Q.top(); Q.pop();
        auto node = q.second;
        if (vis[node.first][node.second]) {
            continue;
        }
        for (int i = 0; i < 4; ++i) {
            int nx = node.first + dx[i];
            int ny = node.second + dy[i];
            if (!valid(nx, ny)) continue;
            if (b[nx][ny] > 0) continue;
            if (a[nx][ny] < 0 && abs(a[nx][ny]) <= a[nx-dx[i]][ny-dy[i]]) {
                a[nx][ny] = a[nx-dx[i]][ny-dy[i]];
                Q.push({a[nx][ny], {nx, ny}});
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            a[i][j] = abs(a[i][j]);
            if (b[i][j] > 0) {
                adj[a[i][j]].push_back({i, j});
            }
        }
    }
    memset(vis, 0, sizeof vis);
    int ans = 0;
    for (int i = 1; i < maxn; ++i) {
        for (auto q : adj[i]) {
            if (!vis[q.first][q.second]) {
                dfs(q.first, q.second);
                ans += 1;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}