/**
 * @author Miguel Mini
 * @tag sorting, bfs
 * @idea
 *      - we can build a new node for
 *      each (node, color).
 *
 *      - new nodes with same color
 *      has edges to neighbors of
 *      associated node with same color.
 *      (this edge has 0-cost)
 *
 *      - connect new nodes to old
 *      associated nodes with cost 1.
 *
 *      - connect old nodes to new
 *      nodes with cost 0.
 *
 *      - run bfs 0/1
 * @complexity O(m\log m + n)
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
vector<int> g[maxn * 5];
int n, m;
vector<pair<int, int>> nd;
int l[maxn], r[maxn];
int d[maxn * 5];

int get_pos(int u, int c) {
    int lo = l[u], hi = r[u];
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (nd[mid].second <= c) lo = mid;
        else hi = mid-1;
    }
    return lo;
}

int bfs(int src, int snk) {
    deque<int> Q;
    memset(d, 1, sizeof d);
    for (int i = l[src]; i <= r[src]; ++i) {
        Q.push_back(i);
        d[i] = 1;
    }
    while (!Q.empty()) {
        int q = Q.front(); Q.pop_front();
        for (auto nxt : g[q]) {
            if (nxt >= nd.size()) {
                if (d[q] + 1 < d[nxt]) {
                    d[nxt] = d[q] + 1;
                    Q.push_back(nxt);
                }
            } else {
                if (d[q] < d[nxt]) {
                    d[nxt] = d[q];
                    Q.push_front(nxt);
                }
            }
        }
    }
    int ans = n + 1;
    for (int i = l[snk]; i <= r[snk]; ++i) {
        ans = min(ans, d[i]);
    }
    if (ans <= n) return ans;
    return -1;
}

int main() {
    scanf("%d%d", &n, &m);
    vector<pair<int, pair<int, int>>> edges;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        edges.push_back({c, {a, b}});
        nd.push_back({a, c});
        nd.push_back({b, c});
    }
    sort(nd.begin(), nd.end());
    nd.resize(unique(nd.begin(), nd.end()) - nd.begin());
    memset(l, -1, sizeof l);
    for (int i = 1; i <= n; ++i) r[i] = -2;
    for (int i = 0; i < nd.size(); ++i) {
        if (l[nd[i].first] == -1) {
            l[nd[i].first] = i;
        }
        r[nd[i].first] = i;
    }
    for (auto e : edges) {
        int u = e.second.first, v = e.second.second, w = e.first;
        g[get_pos(u, w)].push_back(get_pos(v, w));
        g[get_pos(v, w)].push_back(get_pos(u, w));
    }
    for (int i = 0; i < nd.size(); ++i) {
        g[nd.size() + nd[i].first].push_back(i);
        g[i].push_back(nd.size() + nd[i].first);
    }
    printf("%d\n", bfs(1, n));
    return 0;
}