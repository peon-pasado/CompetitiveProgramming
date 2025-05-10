#include <bits/stdc++.h>
using namespace std;
const int maxN = 110;
int sz[maxN], v[maxN];
long long memo[maxN][maxN];
vector<int> g[maxN];
int n, k;
long long ans = 0;

void dfs(int x, int parent=-1) {
	sz[x] = 1;
	for (int _ = 0; _ < g[x].size(); ++_) {
		int v = g[x][_];
		if (v == parent) continue;
		dfs(v, x);
		sz[x] += sz[v];
	}
	for (int i = 0; i <= k; ++i) memo[x][i] = 0;
	memo[x][1] = v[x];
	for (int _ = 0; _ < g[x].size(); ++_) {
		int v = g[x][_];
		if (v == parent) continue;
		for (int i = min(sz[x], k); i > 0; --i) {
			for (int j = 0; j < min(i, sz[v]+1); ++j) {
				memo[x][i] = max(memo[x][i], memo[x][i - j] + memo[v][j]);
			}
		}
	}
	ans = max(ans, memo[x][k]);
}

int main() {
	while (cin >> n >> k) {
		for (int i = 0; i < n; ++i) cin >> v[i];
		for (int i = 0; i < n; ++i) g[i].clear();
		for (int i = 1; i <= n-1; ++i) {
			int u, v; 
			cin >> u >> v;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		ans = 0;
		dfs(0);
		cout << ans << endl;
	}
	return 0;
}	