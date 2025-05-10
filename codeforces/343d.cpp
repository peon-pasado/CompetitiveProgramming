#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 10;
vector<int> g[maxn];
int st[maxn], en[maxn];
int T = 0;
int big[maxn];
int node[maxn];
int sz[maxn];
int h[maxn];
vector<int> F[maxn], E[maxn], Q[maxn];

void dfs(int x, int p) {
	node[T] = x;
	st[x] = T++;
	sz[x] = E[x].size();
	big[x] = -1;
	if (p >= 0) h[x] = h[p]+1;
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

multiset<int> empty_set;
multiset<int> fill_set;
void add(int x) {
	for (int v : E[x]) 
		empty_set.insert(v);
}

void erase(int x) {
	for (int v : E[x]) {
		empty_set.erase(empty_set.find(v));
	}
}

int ans[maxn];
void dsu(int x, int p, bool keep) {
	for (int v : F[x]) fill_set.insert(v);
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
	for (int v : Q[x]) {
		auto id_fill = *prev(fill_set.upper_bound(v));
		auto id_empty = *prev(empty_set.upper_bound(v));
		ans[v] = id_fill > id_empty;
	}
	if (!keep)
		for (int i = st[x]; i <= en[x]; ++i) {
			erase(node[i]);
		}
	for (int v : F[x]) fill_set.erase(fill_set.find(v));
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	for (int i = 2; i <= n; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	int m;
	cin >> m;
	vector<int> need_ans;
	for (int i = 0; i < m; ++i) {
		int c, v;
		cin >> c >> v;
		if (c == 1) F[v].push_back(i);
		if (c == 2) E[v].push_back(i);
		if (c == 3) {
			need_ans.push_back(i);
			Q[v].push_back(i);
		}
	}
	dfs(1, -1);
	fill_set.insert(-2);
	empty_set.insert(-1);
	dsu(1, -1, 1);
	for (int v : need_ans) cout << ans[v] << '\n';
	return 0;
}