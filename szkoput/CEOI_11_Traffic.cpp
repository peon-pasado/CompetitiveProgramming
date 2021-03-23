/**
 * @author Miguel Mini
 * @tag dfs, sorting
 * @idea
 *      - we can see that the nodes reach
 *      a continuous range of non-isolated nodes.
 *
 *      - we can preprocess maximum (minimum) in
 *      O(n+m) if sorting increasing (decreasing).
 *      keeping in a dfs the maximum (minimum)
 *      to the right.
 *
 *      - In addition, we must remove nodes that
 *      are not reachable from the right
 * @complexity O(n \log(n) + m)
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 10;
int x[maxn], y[maxn];
vector<int> g[maxn], gt[maxn];
int n, m, A, B;
int hi[maxn], lo[maxn];
bool vis[maxn];

const int inf = 1e9;
bool ok = 1;
int L = inf;
void dfslo(int v) {
    vis[v] = 1;
    for (int u : g[v]) {
        if (!vis[u]) dfslo(u);
        if (x[u] == A) L = min(L, y[u]);
    }
}

int R = -inf;
void dfshi(int v) {
    vis[v] = 1;
    for (int u : g[v]) {
        if (!vis[u]) dfshi(u);
        if (x[u] == A) R = max(R, y[u]);
    }
}

void dfs(int x) {
    vis[x] = 1;
    for (int v : gt[x]) {
        if (!vis[v]) dfs(v);
    }
}

int main() {
    scanf("%d%d%d%d", &n, &m, &A, &B);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", x+i, y+i);
    }
    for (int i = 0; i < m; ++i) {
        int c, d, k;
        scanf("%d%d%d", &c, &d, &k);
        c--; d--;
        g[c].push_back(d);
        gt[d].push_back(c);
        if (k == 2) {
            g[d].push_back(c);
            gt[c].push_back(d);
        }
    }
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](int i, int j) {
        return y[i] < y[j];
    });
    for (int i : id) {
        if (x[i] == 0) {
            dfshi(i);
            hi[i] = R;
        }
    }
    memset(vis, 0, sizeof vis);
    reverse(id.begin(), id.end());
    for (int i : id) {
        if (x[i] == 0) {
            dfslo(i);
            lo[i] = L;
        }
    }
    vector<int> arr;
    for (int i = 0; i < n; ++i) {
        if (x[i] == A && vis[i]) {
            arr.push_back(y[i]);
        }
    }
    sort(arr.begin(), arr.end());
    vector<pair<int, int>> ans(n);
    memset(vis, 0, sizeof vis);
    for (int i = 0; i < n; ++i) {
        if (x[i] == A) dfs(i);
    }
    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            ans[i] = {i, 0};
            continue;
        }
        ans[i].second = upper_bound(arr.begin(), arr.end(), hi[i])
                        - lower_bound(arr.begin(), arr.end(), lo[i]);
        ans[i].first = i;
    }
    sort(ans.begin(), ans.end(), [](pair<int, int> p, pair<int, int> q) {
        return y[p.first] > y[q.first];
    });
    for (int i = 0; i < n; ++i) {
        if (x[ans[i].first] == 0) {
            printf("%d\n", ans[i].second);
        }
    }
    return 0;
}
