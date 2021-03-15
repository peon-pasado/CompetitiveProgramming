/**
 * @author Miguel Mini
 * @tag dp, rerooting, dfs
 * @idea
 *      - we can notice that if we
 *      consider parity, each node
 *      has a continuous range.
 *
 *      - we can rooting the tree
 *      and obtain a feasible answer
 *      to root.
 *
 *      - and later push this answer.
 *
 *      note: we must maintain the parity.
 */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int l[maxn][2], r[maxn][2];
vector<int> g[maxn];
int n;

void dfs(int x, int p=0) {
    for (int v : g[x]) {
        if (v == p) continue;
        dfs(v, x);
        for (int i = 0; i < 2; ++i) {
            l[x][i] = max(l[x][i], l[v][1-i] - 1);
            r[x][i] = min(r[x][i], r[v][1-i] + 1);
        }
    }
}

void dfs_root(int x, int p=0) {
    if (p) {
        for (int i = 0; i < 2; ++i) {
            l[x][i] = max(l[x][i], l[p][1-i] - 1);
            r[x][i] = min(r[x][i], r[p][1-i] + 1);
        }
    }
    if (l[x][0]%2 == 1) l[x][0] += 1;
    if (l[x][1]%2 == 0) l[x][1] += 1;
    r[x][0] = min(r[x][0], l[x][0]);
    r[x][1] = min(r[x][1], l[x][1]);
    for (int v : g[x]) {
        if (v == p) continue;
        dfs_root(v, x);
    }
}

int ans[maxn];
bool check(int x, int p, int d) {
    if (l[x][d] > r[x][d]) return 0;
    ans[x] = l[x][d];
    for (int v : g[x]) {
        if (v == p) continue;
        if (!check(v, x, 1-d)) return 0;
    }
    return 1;
}

int main() {
    cin >> n;
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 1; i <= n; ++i) {
        l[i][0] = l[i][1] = -1e9;
        r[i][0] = r[i][1] = 1e9;
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int u, p;
        cin >> u >> p;
        l[u][0] = l[u][1] = p;
        r[u][0] = r[u][1] = p;
    }
    dfs(1, 0);
    dfs_root(1, 0);
    bool isans = 0;
    if (check(1, 0, 0)) isans = 1;
    else if (check(1, 0, 1)) isans = 1;
    if (!isans) cout << "No\n";
    else {
        cout << "Yes\n";
        for (int i = 1; i <= n; ++i) {
            cout << ans[i] << '\n';
        }
    }
    return 0;
}