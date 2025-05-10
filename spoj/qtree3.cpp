#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int ll[maxn], rr[maxn], h[maxn];
vector<int> g[maxn];
int n, q;
using pii = pair<int, int>;
set<pii> st[maxn<<2];

void dfs(int x, int p, int& t) {
	h[x] = h[p] + 1;
	ll[x] = t++;
	for (int v : g[x]) {	
		if (v == p) continue;
		dfs(v, x, t);
	}
	rr[x] = t-1;
}

void put(int nx, int x) {
	if (st[nx].count(pii(h[x], x))) {
		st[nx].erase(pii(h[x], x));
	} else {
		st[nx].insert(pii(h[x], x));
	}	
}

int get(int nx) {
	if (st[nx].empty()) return -1;
	return (st[nx].begin())->second;
}

void update(int ll, int rr, int x, int nx=1, int l=0, int r=n-1) {
	if (rr < l or r < ll) return;
	if (ll <= l and r <= rr) {put(nx, x); return;}
	int mid = (l+r)/2;
	update(ll, rr, x, nx<<1, l, mid);
	update(ll, rr, x, nx<<1|1, mid+1, r);
}

int query(int pos, int nx=1, int l=0, int r=n-1) {
	if (pos < l or r < pos) return -1;
	if (l == r) return get(nx);	
	int ans = get(nx);
	if (~ans) return ans;
	int mid = (l+r)/2;
	return query(pos, nx<<1, l, mid) + query(pos, nx<<1|1, mid+1, r) + 1;
}

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 0; i < n-1; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		g[a].emplace_back(b);
		g[b].emplace_back(a);
	}
	int t=0;
	dfs(1, 0, t);
	while (q--) {
		int type, v;
		scanf("%d%d", &type, &v);
		if (type == 0) update(ll[v], rr[v], v);
		else printf("%d\n", query(ll[v]));
	}
	return 0;
}