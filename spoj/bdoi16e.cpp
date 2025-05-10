#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
using ll = long long;
using ii = pair<int, int>;
vector<int> g[maxn];
int sz[maxn];
int big[maxn];
int h[maxn];
int lo[maxn], hi[maxn];
int ver[maxn];
ll val[maxn];
int c[maxn], d[maxn];
int T;

void dfs(int x, int p, ll s_val) {
	ver[T] = x;
	lo[x] = T++;
	h[x] = p==-1? 0 : h[p] + 1;
	val[x] = s_val + c[x];
	sz[x] = 1;
	big[x] = -1;
	for (int v : g[x]) {
		if (v == p) continue;	
		dfs(v, x, s_val + d[v]);
		if (big[x]<0||sz[big[x]]<sz[v]) {
			big[x] = v;
		}
		sz[x] += sz[v];
	}
	hi[x] = T-1;
}

set<ll> so;
void add(int x) {
	so.insert(val[x]);
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
	ans[x] = so.size();
	if (!keep) {
		so.clear();
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
	for (int i = 1; i <= n; ++i) {
		int pi;
		cin >> pi;
		g[pi].push_back(i);
	}
	for (int i = 1; i <= n; ++i) {
		cin >> d[i];
	}
	dfs(0, -1, 0);
	dsu(0, -1, 1);
	for (int i = 1; i <= n; ++i) {
		cout << ans[i] << '\n';
	}
	return 0;
}