/**
 *  @auhor Miguel Mini
 *  @tag dfs, lca, sets
 *  @idea 
 *      = core observation: if there is and correct answer,
 *      then exist an answer with y <= x + 1. 
 *
 *      - a beatiful generalization to this proof can be found here https://www.youtube.com/watch?v=rwiEiGqgetU
 *
**/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
vector<int> g[maxn];
using pii = pair<int, int>;
int n, m, q;
int a[maxn];
int st[maxn][18];
int h[maxn];
set<int> cnt[2][maxn];

int T = 0;
void dfs(int x, int p) {
    h[x] = h[p] + 1;
    st[x][0] = p;
    for (int k = 1; k < 18; ++k) {
        st[x][k] = st[st[x][k-1]][k-1];
    }
    for (int v : g[x]) {
        if (v == p) continue;
        dfs(v, x);
    }
}

int lca(int x, int y) {
    if (h[x] > h[y]) swap(x, y);
    for (int k = 17; k >= 0; --k) {
        if (h[st[y][k]] >= h[x]) {
            y = st[y][k];
        }
    }
    if (x == y) return x;
    for (int k = 17; k >= 0; --k) {
        if (st[x][k] != st[y][k]) {
            x = st[x][k];
            y = st[y][k];
        }
    }
    return st[x][0];
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= m; ++i) {
        scanf("%d", a+i);
    }
    for (int i = 1; i <= m; ++i) {
        cnt[0][a[i]].insert(i);
        if (i < m) {
            cnt[1][lca(a[i], a[i+1])].insert(i);
        }
    }
    while (q--) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            int pos, v;
            scanf("%d%d", &pos, &v);
            if (pos < m) {
                cnt[1][lca(a[pos], a[pos+1])].erase(pos);
            }
            if (pos > 1) {
                cnt[1][lca(a[pos-1], a[pos])].erase(pos-1);
            }
            cnt[0][a[pos]].erase(pos);
            a[pos] = v;
            cnt[0][a[pos]].insert(pos);
            if (pos < m) {
                cnt[1][lca(a[pos], a[pos+1])].insert(pos);
            }
            if (pos > 1) {
                cnt[1][lca(a[pos-1], a[pos])].insert(pos-1);
            }
        } else {
            int l, r, v;
            scanf("%d%d%d", &l, &r, &v);
            bool ok = 0;
            auto q = cnt[0][v].lower_bound(l);
            if (q != cnt[0][v].end() && *q <= r) {
                printf("%d %d\n", *q, *q);
                continue;
            }
            auto u = cnt[1][v].lower_bound(l);
            if (u != cnt[1][v].end() && *u < r) {
                printf("%d %d\n", *u, *u + 1);
            } else {
                puts("-1 -1");
            }
            
        }
    }
    return 0;
}
