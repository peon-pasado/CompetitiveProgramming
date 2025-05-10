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
int h[maxn];
int best[1<<22];
int ss[maxn];

void dfs(int x, int p) {
	node[T] = x;
	st[x] = T++;
	sz[x] = 1;
	big[x] = -1;
	if (p >= 0) {
		h[x] = h[p] + 1;
		ss[x] = (1<<c[x]-'a') ^ ss[p];
	}
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
	best[ss[x]] = max(best[ss[x]], h[x]);
}

void erase(int x) {
	best[ss[x]] = -1e9;
}

int query(int r, int x) {
	int ans = 0;
	ans = max(ans, best[ss[x]] + h[x] - 2 * h[r]);
	for (int i = 0; i < 22; ++i) {
		ans = max(ans, best[ss[x] ^ (1<<i)] + h[x] - 2 * h[r]);
	}
	return ans;
}

int ans[maxn];
void dsu(int x, int p, bool keep) {
	for (int v : g[x]) {
		if (v == p || v == big[x]) continue;
		dsu(v, x, 0);
	}
	if (~big[x]) dsu(big[x], x, 1);
	add(x);
	ans[x] = query(x, x);
	for (int v : g[x]) {
		if (v == p) continue;
		ans[x] = max(ans[x], ans[v]);
		if (v == big[x]) continue;
		for (int i = st[v]; i <= en[v]; ++i) {
			ans[x] = max(ans[x], query(x, node[i]));
		}	
		for (int i = st[v]; i <= en[v]; ++i) {
			add(node[i]);
		}
	}
	if (!keep)
		for (int i = st[x]; i <= en[x]; ++i) {
			erase(node[i]);
		}
}

int main() {
	for (int i = 0; i < 1<<22; ++i) best[i] = -1e9;
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	for (int i = 2; i <= n; ++i) {
		int pi;
		cin >> pi;
		cin.get();
		c[i] = cin.get();
		g[pi].push_back(i);
	}
	dfs(1, -1);
	dsu(1, -1, 1);
	for (int i = 1; i <= n; ++i) {
		cout << ans[i] << ' ';
	}
	cout << '\n';
	return 0;
}