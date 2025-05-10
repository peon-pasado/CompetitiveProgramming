#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
#include <numeric>
#include <map>
using namespace std;

const int maxn = 110;
vector<int> g[maxn];
char state[maxn];
int depth[maxn];
int low[maxn];
bool cuts[maxn];
string t[maxn];
int T;

void dfs(int x, int p = 0)
{
    depth[x] = low[x] = T++;
    state[x] = 1;
    int n_branch = 0;
    for (int v : g[x])
    {
        if (v == p)
            continue;
        if (state[v] == 0)
        {
            dfs(v, x);
            n_branch++;
            low[x] = min(low[x], low[v]);
            if (low[v] >= depth[x] && p != 0)
            {
                cuts[x] = 1;
            }
        }
        else
        {
            low[x] = min(low[x], depth[v]);
        }
    }
    if (p == 0 && n_branch > 1)
    {
        cuts[x] = 1;
    }
    state[x] = 2;
}

void init(int n) {
    T = 0;
    for (int i = 1; i <= n; ++i)
    {
        state[i] = 0;
        cuts[i] = 0;
    }
}

int main()
{
    int tc = 1;
    int n;
    while (cin >> n, n) {
        map<string, int> id;
        for (int i = 1; i <= n; ++i) {
            string s;
            cin >> s;
            t[i] = s;
            id[s] = i;
        }
        for (int i = 1; i <= n; ++i)
            g[i].clear();
        init(n);
        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            string u, v;
            cin >> u >> v;
            int iu = id[u];
            int iv = id[v];
            g[iu].emplace_back(iv);
            g[iv].emplace_back(iu);
        }
        for (int i = 1; i <= n; ++i) {
            if (state[i] == 0)
                dfs(i, 0);
        }
        if (tc > 1) cout << '\n';
        cout << "City map #" << tc++ << ": ";
        cout << accumulate(cuts, cuts+n+1, 0) << " camera(s) found\n";
        for (auto e : id) {
            if (cuts[e.second]) cout << e.first << '\n';
        }
    }
    return 0;
}
