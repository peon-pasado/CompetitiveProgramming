#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
vector<int> g[maxn];
int c[maxn], st[maxn], en[maxn];
int T = 0;
int big[maxn];
int node[maxn];
int sz[maxn];
map<int, int> colors[2 * maxn];
int D[2 * maxn];
int h[maxn];
vector<pair<int, int>> Q[maxn];

void dfs(int x, int p) {
	node[T] = x;
	st[x] = T++;
	sz[x] = 1;
	big[x] = -1;
	h[x] = p==-1?0:h[p]+1;
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
	if (x == 0) return;
	auto& y = colors[h[x]][c[x]];
	if (y == 0) D[h[x]]++;
	y++;
}

void erase(int x) {
	if (x == 0) return;
	auto& y = colors[h[x]][c[x]];
	if (y == 1) D[h[x]]--;
	y--;
}


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
		ans[q.second] = D[q.first + h[x]]; 
	}
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
	map<string, int> id;
	int ti=0;
	for (int i = 1; i <= n; ++i) {
		string s;
		int pi;
		cin >> s >> pi;
		if (!id.count(s)) {
			id[s] = ti++;
		}
		c[i] = id[s];
		g[pi].push_back(i);
	}
	int m;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		int v, k;
		cin >> v >> k;
		Q[v].push_back({k, i});
	}
	dfs(0, -1);
	dsu(0, -1, 1);
	for (int i = 0; i < m; ++i) {
		cout << ans[i] << '\n';
	}
	cout << '\n';
	return 0;
}