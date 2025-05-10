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

const int maxn = 10010;
vector<int> g[maxn];
char state[maxn];
int depth[maxn];
int low[maxn];
bool cuts[maxn];
int T;

void dfs(int x, int p = 0) {
    depth[x] = low[x] = T++;
    state[x] = 1;
    int n_branch = 0;
    for (int v : g[x]) {
        if (v == p)
            continue;
        if (state[v] == 0) {
            dfs(v, x);
            n_branch++;
            low[x] = min(low[x], low[v]);
            if (low[v] >= depth[x] && p != 0) {
                cuts[x] = 1;
            }
        } else {
            low[x] = min(low[x], depth[v]);
        }
    }
    if (p == 0 && n_branch > 1) {
        cuts[x] = 1;
    }
    state[x] = 2;
}

void init(int n) {
    T = 0;
    for (int i = 1; i <= n; ++i) {
        state[i] = 0;
        cuts[i] = 0;
    }
}

int main() {
    int t;
    cin >> t;
    int tc=1;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            g[i].clear();
        }
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        init(n);
        dfs(1);
        cout << "Case " << tc++ << ": " << accumulate(cuts, cuts+n+1, 0) << '\n';  
    }
	return 0;
}
