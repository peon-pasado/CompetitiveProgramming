/**
 * @author Miguel Mini
 * @tag dfs, centroid
 * @idea
 *      - find the centroid.
 */ 

#include <bits/stdc++.h>
using namespace std;

const int maxn = 16010;
int sz[maxn];
vector<int> g[maxn];
int n;

void dfs_sz(int x, int p) {
    sz[x] = 1;
    for (int v : g[x]) {
        if (v == p) continue;
        dfs_sz(v, x);
        sz[x] += sz[v];
    }
}

int temp;
using ii = pair<int, int>;
ii centroid(int x, int p, int n) {
    temp = n-sz[x];
    for (int v : g[x]) {
        if (v == p) continue;
        if (2 * sz[v] > n) {
            return centroid(v, x, n);
        } else if (2 * sz[v] == n) {
            return {x, v};
        }
        temp = max(temp, sz[v]);
    }
    return {x, -1};
}

int main() {
    freopen("sediu.in", "r", stdin);
    freopen("sediu.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs_sz(1, 0);
    auto q = centroid(1, 0, n);
    if (q.second == -1) {
        printf("%d 1\n%d\n", temp, q.first);
    } else {
        if (q.first > q.second) swap(q.first, q.second);
        printf("%d 2\n%d %d\n", n/2, q.first, q.second);
    }
    return 0;
}