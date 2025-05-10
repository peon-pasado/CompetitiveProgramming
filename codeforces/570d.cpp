#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 10;
using ll = long long;
vector<int> g[maxn];
int c[maxn], st[maxn], en[maxn];
int T = 0;
int big[maxn];
int node[maxn];
int sz[maxn];
int fr[maxn];
int h[maxn];

void dfs(int x, int p) {
	h[x] = h[p] + 1;
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
	fr[h[x]] ^= (1<<c[x]);
}

void erase(int x) {
	fr[h[x]] ^= (1<<c[x]);
}


vector<pair<int, int>> Q[maxn];
bool ans[maxn];
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
		ans[q.first] = __builtin_popcount(fr[q.second]) <= 1;	
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
	cin.get();
	for (int i = 2; i <= n; ++i) {
		int pi;
		cin >> pi;
		g[pi].push_back(i);
	}
	cin.get();
	for (int i = 1; i <= n; ++i) {
		c[i] = cin.get() - 'a';
	}
	for (int i = 0; i < m; ++i) {
		int v, h;
		cin >> v >> h;
		Q[v].push_back({i, h});
	}
	dfs(1, 0);
	dsu(1, 0, 1);
	for (int i = 0; i < m; ++i) {
		cout << (ans[i] ? "Yes" : "No") << '\n';
	}
	return 0;
}