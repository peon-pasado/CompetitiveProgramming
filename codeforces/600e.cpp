#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
using ll = long long;
vector<int> g[maxn];
int c[maxn], st[maxn], en[maxn];
int T = 0;
int big[maxn];
int node[maxn];
ll sum[maxn];
int sz[maxn];
int fr[maxn];
int max_fr;

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

void add(int x) {
	sum[fr[c[x]]] -= c[x];
	fr[c[x]] += 1;
	sum[fr[c[x]]] += c[x];
	max_fr = max(max_fr, fr[c[x]]);
}

void erase(int x) {
	sum[fr[c[x]]] -= c[x];
	fr[c[x]] -= 1;
	sum[fr[c[x]]] += c[x];
	if (sum[max_fr] == 0) max_fr--;
}

ll ans[maxn];
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
	ans[x] = sum[max_fr];
	if (!keep)
		for (int i = st[x]; i <= en[x]; ++i) {
			erase(node[i]);
		}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> c[i];
	}
	for (int i = 1; i <= n-1; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	sum[0] = accumulate(c+1, c+n+1, 0ll);
	dfs(1, -1);
	dsu(1, -1, 1);
	for (int i = 1; i <= n; ++i) {
		cout << ans[i] << ' ';
	}
	cout << '\n';
	return 0;
}