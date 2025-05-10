#include <bits/stdc++.h>
using namespace std;
const int maxN = 2e5 + 10;
int n;
struct Node {
	int u, l;
};
vector<Node> g[maxN];
vector<int> cycle;
vector<int> path;
char vis[maxN];
void dfs(int x, int p=0) {
	vis[x] = 1;
	path.push_back(x);
	for (auto node : g[x]) {
		if (node.u == p) continue;
		if (not vis[node.u]) dfs(node.u, x);
		else if (vis[node.u] == 1) {
			reverse(begin(path), end(path));
			for (int e : path) {			
				cycle.push_back(e);
				if (e == node.u) break;
			}
		}
	}
	vis[x] = 2;
	path.pop_back();
}

long long dp[maxN];
long long best[maxN];
void calc(int x) {
	vis[x] = 1;
	dp[x] = 0;
	vector<long long> two = {0ll, 0ll};
	for (auto node : g[x]) {
		if (not vis[node.u]) {
			calc(node.u);
			dp[x] = max(dp[x], dp[node.u]);
			two.push_back(best[node.u] + node.l);
			sort(begin(two), end(two), greater<long long>());
			two.pop_back();
		}
	}
	best[x] = two[0];
	dp[x] = max(dp[x], two[0] + two[1]);
}
struct stNode {
	long long sum, pref, suff, ma;
	bool operator ==(stNode p) {
		return sum == p.sum and pref == p.pref and suff == p.suff and ma == p.ma;
	}
} st[maxN<<3];
stNode nil = {-1, -1, -1, -1};

vector<int> a;
map<pair<int, int>, int> edge;
stNode merge(stNode p, stNode q, int mid) {
	if (q == nil) return p;
	if (p == nil) return q;
	int e = edge[{a[mid], a[mid+1]}];
	return {
		p.sum + q.sum + e,
		max(p.pref, p.sum + e + q.pref),	
		max(q.suff, q.sum + e + p.suff),
		max(max(p.ma, q.ma), p.suff + e + q.pref)
	};
}

void build(int nx, int l, int r) {
	if (l == r) {
		st[nx] = {0ll, best[a[r]], best[a[r]], dp[a[r]]};
		return;
	}
	int mid = (l + r)/2;
	build(nx<<1, l, mid);
	build(nx<<1|1, mid+1, r);
	st[nx] = merge(st[nx<<1], st[nx<<1|1], mid);
}

stNode query(int a, int b, int nx, int l, int r) {
	if (b < l or r < a) return nil;
	if (a <= l and r <= b) return st[nx];
	int mid = (l + r) / 2;
	auto L = query(a, b, nx<<1, l, mid);
	auto R = query(a, b, nx<<1|1, mid+1, r);
	return merge(L, R, mid);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		int u, v, l;
		scanf("%d %d %d", &u, &v, &l);
		g[u].push_back({v, l});
		g[v].push_back({u, l});
		edge[{v, u}] = edge[{u, v}] = l;
	}
	dfs(1);
	memset(vis, 0, sizeof vis);
	for (int e : cycle) {
		vis[e] = 1;
	}
	for (int e : cycle) {
		calc(e);
	}
	for (int i = 0; i < 2; ++i) {
		for (int e : cycle) {
			a.push_back(e);
		}
	}
	int m = cycle.size();
	build(1, 0, 2*m-2);
	long long ans = 1e18;
	for (int i = 0; i < m; ++i) {
		ans = min(ans, query(i, i+m-1, 1, 0, 2*m-2).ma);
	}
	printf("%lld\n", ans);
	return 0;
}