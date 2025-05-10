#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int maxN = 2e4 + 10;
int t, n;
vector<int> g[maxN];
int sz[maxN], ans[maxN];

void dfs(int x, int parent=0) {
	sz[x] = 1;
	ans[x] = 0;
	for (int i = 0; i < g[x].size(); ++i) {
		int v = g[x][i];
		if (v == parent) continue;
		dfs(v, x);
		sz[x] += sz[v];
		ans[x] = max(ans[x], sz[v]);
	}
	ans[x] = max(ans[x], n - sz[x]);
}

int main() {
	cin >> t;
	for (int _ = 1; _ <= t; ++_) {
		cin >> n;
		for (int i = 1; i <= n; ++i) g[i].clear();
		for (int i = 1; i <= n-1; ++i) {
			int u, v; cin >> u >> v;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		dfs(1);
		int f = n, cnt = 0;
		for (int i = 1; i <= n; ++i) {
			if (f > ans[i]) {
				f = ans[i];
				cnt = i;
			}
		}
		cout << cnt << " " << f << endl;
	}
	return 0;
}