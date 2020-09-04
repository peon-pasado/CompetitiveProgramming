/**
 * @author Miguel Mini
 * @tag dijkstra, dfs, dp, dijkstra_dag
 * @idea
 *      - we can make n dijkstra dags, for 
 *      every node. given these we can count
 *      the numbers of shortest path over a edge 
 *      with two dps, over dag and over tranpose 
 *      dag (dag too).
**/ 
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1510;
const int maxm = 5010;
using ii = pair<int, int>;
vector<int> g[maxn], gt[maxn];
struct Edge {
   int a, b, len;
} edges[maxm];
int ans[maxm];
int d[maxn];
int n, m;
bool vis[maxn];
int L[maxn], R[maxn];

const int mod = 1e9 + 7;
int add(int a, int b) {
    return a+b < mod ? a+b : a+b-mod;
}

int mul(long long a, long long b) {
    return a * b % mod;
}

void dfs(int x) {
    if (vis[x]) return;
    vis[x] = 1;
    R[x] = 1;
    for (int ie : g[x]) {
        int v = edges[ie].b;
        if (d[x] + edges[ie].len == d[v]) {
            dfs(v);
            R[x] = add(R[x], R[v]);
        }
    }
}

void dfs_r(int r, int x) {
    if (vis[x]) return;
    vis[x] = 1;
    L[x] = x == r;
    for (int ie : gt[x]) {
        int v = edges[ie].a;
        if (d[v] + edges[ie].len == d[x]) {
            dfs_r(r, v);
            L[x] = add(L[x], L[v]);
        }
    }
}

void dijkstra(int src) {
    for (int i=1; i<=n; ++i) d[i] = 1e9;
    d[src] = 0;
    priority_queue<ii, vector<ii>, greater<ii>> q;
    q.emplace(d[src], src);
    while (!q.empty()) {
        auto e = q.top(); q.pop();
        if (e.first != d[e.second]) continue;
        for (int ie : g[e.second]) {
            int temp = e.first+edges[ie].len;
            int v = edges[ie].b;
            if (temp < d[v]) {
                d[v] = temp;
                q.emplace(d[v], v);
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i=0; i<m; ++i) {
        int a, b, l;
        scanf("%d%d%d", &a, &b, &l);
        g[a].emplace_back(i);
        gt[b].emplace_back(i);
        edges[i] = {a, b, l};
    }
    for (int i=1; i<=n; ++i) {
        dijkstra(i);
        memset(vis, 0, sizeof vis);
        dfs(i);
        memset(vis, 0, sizeof vis);
        for (int j = 1; j <= n; ++j) dfs_r(i, j);
        for (int j=0; j<m; ++j) {
            if (d[edges[j].a] + edges[j].len != d[edges[j].b]) continue;
            int temp = mul(L[edges[j].a], R[edges[j].b]);
            ans[j] = add(ans[j], temp);
        }
    }
    for (int i=0; i<m; ++i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
