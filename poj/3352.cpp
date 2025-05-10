#include <iostream>
#include <vector>
using namespace std;

const int maxn = 1e3 + 5;
vector<int> g[maxn];

void add_edge(int x, int y) {
    g[x].push_back(y);
    g[y].push_back(x);
}

int sum[maxn];
int state[maxn];
int dfs(int x, int p) {
    int ans = 0;
    sum[x] = 0;
    state[x] = 1;
    for (int i=0; i<g[x].size(); ++i) {
        int u = g[x][i];
        if (u == p) continue;
        if (state[u] == 0) {
            ans += dfs(u, x);
            sum[x] += sum[u];
        } else {
            sum[x] += state[u];
        }
    }
    state[x] = -1;
    if (p != 0 && sum[x]==0 && ans == 0) {
        ans += 1;
    }
    return ans;
}

int main() {
    int n, m;
    cin>>n>>m;
    for (int i=0; i<m; ++i) {
        int a, b;
        cin>>a>>b;
        add_edge(a, b);
    }
    int n_bridges = dfs(1, 0);
    cout << (n_bridges + 1)/2 << '\n';
    return 0;
}