#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
#include <numeric>
using namespace std;

const int maxn = 1010;
vector<int> g[maxn];
char state[maxn];
int depth[maxn];
int low[maxn];
int T;
vector<pair<int, int>> edges;

void dfs(int x, int p = -1) {
    depth[x] = low[x] = T++;
    state[x] = 1;
    for (int v : g[x]) {
        if (v == p)
            continue;
        if (state[v] == 0) {
            dfs(v, x);
            low[x] = min(low[x], low[v]);
            if (low[v] > depth[x]) {
                edges.push_back({min(v, x), max(x, v)});
            }
        } else {
            low[x] = min(low[x], depth[v]);
        }
    }
    state[x] = 2;
}

void init(int n) {
    T = 0;
    for (int i = 0; i < n; ++i) {
        state[i] = 0;
    }
    edges.clear();
}

int main()
{
    int n;
    int tc = 1;
    while (cin >> n) {
        for (int i = 0; i < n; ++i)
            g[i].clear();
        init(n);
        for (int i = 0; i < n; ++i) {
            int u, m, v;
            scanf("%d (%d)", &u, &m);
            for (int j = 0; j < m; ++j) {
                cin >> v;
                g[u].push_back(v);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (state[i] == 0)
                dfs(i);
        }
        cout << edges.size() << " critical links\n";
        sort(edges.begin(), edges.end());
        for (auto e : edges) {
            cout << e.first << " - " << e.second << '\n';
        }
        cout << "\n";
    }
    return 0;
}
