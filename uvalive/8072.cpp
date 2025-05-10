#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e5 + 10;
int sz[maxN];
long long c[maxN];
int P[maxN];
int edges;
vector<int> g[maxN];

void dfs(int x, int p) {
	P[x] = p;
	sz[x] = c[x] = 0;
	for (int v : g[x]) {
		if (v == p) continue;
		dfs(v, x);
		c[x] += sz[x] *1ll* sz[v];
		sz[x] += sz[v];
	}
	c[x] += sz[x] *1ll* (edges - sz[x]);
	sz[x] += 1;
}

int main() {
	while (cin >> edges) {
	for (int i = 0; i <= edges; ++i) g[i].clear();
	for (int i = 1; i <= edges; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(0, -1);
	int cen = max_element(c, c+edges+1) - c;
	vector<int> d = {edges - sz[cen] + 1, 0};
	for (int v : g[cen]) {	
		if (v == P[cen]) continue;
		d.push_back(sz[v]);
		sort(d.rbegin(), d.rend());
	}
	cout << c[cen] << " " << c[cen] - d[0] * 1ll * d[1] << endl;
	}
	return 0;
}