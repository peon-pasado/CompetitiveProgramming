#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
vector<int> g[maxn];
int st[maxn], en[maxn];
int T = 0;
int big[maxn];
int node[maxn];
int sz[maxn];
int D[maxn];
int h[maxn];
vector<pair<int, int>> Q[maxn];
int spt[maxn][18];

void dfs(int x, int p) {
	node[T] = x;
	st[x] = T++;
	sz[x] = 1;
	big[x] = -1;
	h[x] = p==-1?0:h[p]+1;
	spt[x][0] = p==-1?x:p;
	for (int k = 1; k < 18; ++k) {
		spt[x][k] = spt[spt[x][k-1]][k-1];	
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

int jump(int x, int l) {
	for (int i = 17; i >= 0; --i)
		if (l & (1<<i)) x = spt[x][i];	
	return x;
}

void add(int x) {
	D[h[x]]++;
}

void erase(int x) {
	D[h[x]]--;
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
	if (x > 0) {
		for (auto q : Q[x]) {
			ans[q.second] = D[q.first + h[x]] - 1; 
		}
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
	for (int i = 1; i <= n; ++i) {
		int pi;
		cin >> pi;
		g[pi].push_back(i);
	}
	dfs(0, -1);
	int m;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		int v, k;
		cin >> v >> k;
		Q[jump(v, k)].push_back({k, i});
	}
	dsu(0, -1, 1);
	for (int i = 0; i < m; ++i) {
		cout << ans[i] << ' ';
	}
	cout << '\n';
	return 0;
}