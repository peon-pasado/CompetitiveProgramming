#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e5 + 10;
vector<int> g[maxN];
int a[maxN];
int n, m;
int ans = 0;

void dfs(int node, int p, int cnt) {
	if (cnt + a[node] > m) return;
	bool leaf = 1;
	for (int u : g[node]) {
		if (u == p) continue;
		dfs(u, node, a[node] == 1 ? cnt + 1 : 0);
		leaf = 0;
	}
	if (leaf) {
		ans += 1;
	} 
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	for (int i = 2; i <= n; ++i) {
		int x, y;
		cin >> x >> y;
		g[x].emplace_back(y);
		g[y].emplace_back(x);
	}
	dfs(1, 0, 0);
	cout << ans << endl;
	return 0;
}
