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

void dfs(int x, int p = 0) {
    depth[x] = low[x] = T++;
    state[x] = 1;
    for (int v : g[x]) {
        if (v == p)
            continue;
        if (state[v] == 0) {
            edges.push_back({x, v});
            dfs(v, x);
            low[x] = min(low[x], low[v]);
            if (low[v] > depth[x]) {
                edges.push_back({v, x});
            }
        }
        else {
            if (state[v] == 1) edges.push_back({x, v});
            low[x] = min(low[x], depth[v]);
        }
    }
    state[x] = 2;
}

void init(int n)
{
    T = 0;
    for (int i = 1; i <= n; ++i) {
        state[i] = 0;
    }
    edges.clear();
}

int main()
{
    int n, m;
    int tc=1;
    while (cin >> n >> m, n + m) {
        for (int i = 1; i <= n; ++i)
            g[i].clear();
        init(n);
        for (int i = 1; i <= m; ++i) {
            int a, b;
            cin >> a >> b;
            g[a].emplace_back(b);
            g[b].emplace_back(a);
        }
        dfs(1, 0);
        cout << tc++ << "\n\n";
        for (auto e : edges) {
            cout << e.first << " " << e.second << '\n';
        }
        cout << "#\n";
    }
    return 0;
}
