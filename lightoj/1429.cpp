#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e3 + 10;
int t, n, m;
bool vis[maxn];
vector<int> g[maxn], gt[maxn], dag[maxn];
bitset<maxn> G[maxn];

struct BipartiteMatcher {
	vector<int> L, R;
	vector<bool> vis;
	int n, m;

	void build(int n, int m) {
		this->n = n;
		this->m = m;
		L.clear(); R.clear(); vis.clear();
		L.resize(n, -1);
		R.resize(m, -1); vis.resize(n);
	}
	
	bool match(int x) {
		if (vis[x]) return 0;
		vis[x] = 1;
		for (int v = G[x]._Find_first(); v < m; v = G[x]._Find_next(v))
			if (R[v] == -1)
				return R[L[x] = v] = x, 1;
		for (int v = G[x]._Find_first(); v < m; v = G[x]._Find_next(v))
			if (match(R[v]))
				return R[L[x] = v] = x, 1;
		return 0;
	}

	int solve() {
		int ok = 1;
		while (ok--) {
			fill(begin(vis), end(vis), 0);
			for (int i = 0; i < n; ++i)
				ok |= L[i]==-1 and match(i);
		}	
		int res = 0;
		for (int i = 0; i < n; ++i) res += L[i]!=-1;
		return res;
	}
} BM;

vector<int> order;
void topo(int x) {
	vis[x] = 1;
	for (int v : g[x]) {
		if (not vis[v]) {
			topo(v);
		}
	}
	order.push_back(x);
}

int value[maxn], tempo[maxn];
void dfs(int x, int c) {
	value[x] = tempo[c] = c;
	for (int v : gt[x]) {
		if (not value[v]) {
			dfs(v, c);
		} else if (tempo[value[v]] < c) {
			tempo[value[v]] = c;
			dag[value[v]].push_back(c);
		}
	}
}

int path[maxn];
int main() {
	scanf("%d", &t);
	for (int nc = 1; nc <= t; ++nc) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			g[i].clear();
			gt[i].clear();
		}
		for (int i = 1; i <= m; ++i) {
			int u, v;
			scanf("%d %d", &u, &v);
			g[u].push_back(v);
			gt[v].push_back(u);
		}
		memset(vis, 0, sizeof vis);
		order.clear();
		for (int i = 1; i <= n; ++i) {
			if (not vis[i]) {
				topo(i);
			}
		}
		for (int i = 1; i <= n; ++i) dag[i].clear();
		memset(value, 0, sizeof value);
		memset(tempo, 0, sizeof tempo);
		reverse(begin(order), end(order));
		int color = 0;
		for (int v : order) {
			if (not value[v]) {
				dfs(v, ++color);
			}
		}
		BM.build(color, color);
		for (int c = 0; c < color; ++c) G[c].reset();
		int cut = 0;
		for (int c = color-1; c >= 0; --c) {
			for (int v : dag[c+1]) {
				G[c] |= G[v-1];
				G[c][v-1] = 1;
			}
		}
		printf("Case %d: %d\n", nc, color - BM.solve());
	}
	return 0;
}