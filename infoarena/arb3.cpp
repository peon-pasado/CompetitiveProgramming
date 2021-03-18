/**
 * @author Miguel Mini
 * @tag  dfs, sorting, binary_search
 * @idea
 *      - we can use recursive solution
 *      of node to root.
 *
 *      - if we need y iterations in node x,
 *      we have:
 *
 *          - y + (c[v] - c[x]) iterations
 *          in node v with c[v] >= c[x]
 *
 *          - max(0, y - 1 + (c[v] - c[x])),
 *          in other case.
 *
 *          - v is a brother node of x or x itself.
 *
 *      - we can summarize the sum of iterations:
 *
 *          - let be the set A:
 *
 *              A = {v | y - 1 + c[v] - c[x] >= 0}
 *
 *          - (y - c[x]) * |A| + sum(c[v], v \in A) - (|A|-pos[x])
 *
 *      - we can answer this in O(20 * log(n)) sorting the nodes.
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int c[maxn], pi[maxn], pos[maxn];
vector<int> g[maxn];
int n, q;
using ll = long long;
ll acc[maxn];

int query(int x, int d) {
    if (x == 1) return d;
    int lo = 0, hi = g[pi[x]].size() - 1;
    while (lo < hi) {
        int mid = (hi + lo + 1) / 2;
        if (d - 1 + c[g[pi[x]][mid]] - c[x] >= 0) lo = mid;
        else hi = mid-1;
    }
    return query(pi[x], (d - c[x]) * (lo + 1) + acc[g[pi[x]][lo]] - (lo - pos[x]));
}

int main() {
    freopen("arb3.in", "r", stdin);
    freopen("arb3.out", "w", stdout);
    scanf("%d%d", &n, &q);
    for (int i = 2; i <= n; ++i) {
        scanf("%d", pi + i);
        g[pi[i]].push_back(i);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", c+i);
    }
    for (int i = 1; i <= n; ++i) {
        if (g[i].empty()) continue;
        sort(g[i].begin(), g[i].end(), [&](int i, int j) {
            return c[i] > c[j];
        });
        for (int j = 0; j < g[i].size(); ++j) pos[g[i][j]] = j;
        ll last = 0;
        for (auto v : g[i]) {
            last = acc[v] = c[v] + last;
        }
    }
    for (int i = 1; i <= q; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d\n", query(x, y));
    }
    return 0;
}