#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
using ll = long long;
vector<int> g[maxn];
int c[maxn], st[maxn], en[maxn];
int T = 0;
int big[maxn];
int node[maxn];
int sz[maxn];
int fr[maxn];

void dfs(int x, int p) {
	node[T] = x;
	st[x] = T++;
	sz[x] = 1;
	big[x] = -1;
	for (int v : g[x]) {
		if (v == p) continue;
		dfs(v, x);
		sz[x] += sz[v];
		if (big[x] == -1 || sz[big[x]] < sz[v]) {
			big[x] = v;
		}
	}
	en[x] = T-1;
}

int ft[maxn];
void update(int x, int v) {
	while (x < maxn) {
		ft[x] += v;
		x |= (x+1);
	}
}

int query(int x) {
	int ans = 0;
	while (x >= 0) {
		ans += ft[x];
		x = (x&(x+1))-1;
	}
	return ans;
}

void add(int x) {
	update(fr[c[x]], -1);
	fr[c[x]] += 1;
	update(fr[c[x]], 1);
}

void erase(int x) {
	update(fr[c[x]], -1);
	fr[c[x]] -= 1;
	update(fr[c[x]], 1);
}

vector<pair<int, int>> Q[maxn];
int ans[maxn];
void dsu(int x, int p, bool keep) {
	for (int v : g[x]) {
		if (v == p || v == big[x]) continue;
		dsu(v, x, 0);
	}
	if (~big[x]) dsu(big[x], x, 1);
	add(x);
	for (int v : g[x]) {
		if (v == p || v == big[x]) continue;
		for (int i = st[v]; i <= en[v]; ++i) {
			add(node[i]);
		}
	}
	for (auto q : Q[x]) {
		ans[q.first] = query(maxn-1) - query(q.second-1);
	}
	if (!keep)
		for (int i = st[x]; i <= en[x]; ++i) {
			erase(node[i]);
		}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> c[i];
	}
	for (int i = 1; i <= n-1; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	update(0, n);
	for (int i = 0; i < m; ++i) {
		int v, k;
		cin >> v >> k;
		Q[v].push_back({i, k});
	}
	dfs(1, -1);
	dsu(1, -1, 1);
	for (int i = 0; i < m; ++i) {
		cout << ans[i] << '\n';
	}
	return 0;
}