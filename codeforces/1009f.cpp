#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;
vector<int> g[maxn];
int sz[maxn];
int big[maxn];
int h[maxn];
int lo[maxn], hi[maxn];
int ver[maxn];
int T;

void dfs(int x, int p) {
	ver[T] = x;
	lo[x] = T++;
	h[x] = h[p] + 1;
	sz[x] = 1;
	big[x] = -1;
	for (int v : g[x]) {
		if (v == p) continue;	
		dfs(v, x);
		if (big[x]<0||sz[big[x]]<sz[v]) {
			big[x] = v;
		}
		sz[x] += sz[v];
	}
	hi[x] = T-1;
}

int fr[maxn];
int best = 0;
void add(int x) {
	fr[h[x]]++;
	if (fr[h[x]]>fr[best]) {
		best=h[x];
	} else if (fr[h[x]]==fr[best]) {
		best = min(best, h[x]);
	}
}

void erase(int x) {
	fr[h[x]]--;
}

int ans[maxn];
void dsu(int x, int p, bool keep) {
	for (int v : g[x]) {
		if (v==p || v==big[x]) continue;
		dsu(v, x, 0);
	}
	if (~big[x]) dsu(big[x], x, 1);
	add(x);
	for (int v : g[x]) {
		if (v==p || v==big[x]) continue;
		for (int i=lo[v]; i<=hi[v]; ++i) {
			add(ver[i]);
		}
	}
	ans[x] = best-h[x];
	if (!keep) {
		for (int i=lo[x]; i<=hi[x]; ++i) {
			erase(ver[i]);
		}
		best=0;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	for (int i = 0; i < n-1; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1, 0);
	dsu(1, 0, 1);
	for (int i = 1; i <= n; ++i) {
		cout << ans[i] << '\n';
	}
	return 0;
}