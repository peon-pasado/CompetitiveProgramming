#include <bits/stdc++.h>
using namespace std;
const int maxN = 120;
vector<int> g[maxN];
int n;
bool vis[maxN];
int lo[maxN], up[maxN];
int T;

int dfs(int x, int p = 0) {
	int cuts = 0, is_cut = 0;
	vis[x] = 1;
	lo[x] = up[x] = T++;
	int children = 0;
	for (int v : g[x]) {
		if (v == p) continue;
		if (vis[v]) {
			up[x] = min(up[x], lo[v]);
		} else {
			cuts += dfs(v, x);
			up[x] = min(up[x], up[v]);
			if (lo[x] <= up[v] and p != 0) {
				is_cut = 1;
			}
			children += 1;
		}
	}
	if (p == 0 and children > 1) is_cut = 1;
	return cuts + is_cut;
}

int main() {
	while (cin >> n, n) {
		for (int i = 1; i <= n; ++i) g[i].clear();
		int u, v;
		while (cin >> u, u) {
			string line;
			getline(cin, line);
			istringstream in(line);
			while (in >> v) {
				g[u].push_back(v);
				g[v].push_back(u);
			}	
		}
		memset(vis, 0, sizeof vis);
		T = 0;
		printf("%d\n", dfs(1));
	}
	return 0;
}