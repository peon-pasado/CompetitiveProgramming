#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9; 
struct CentroidDecomposition {
	vector<vector<int>> T;
	vector<int> sz, P, rank;
	vector<bool> block;
	vector<vector<int>> dist;
	vector<multiset<int>> res;
	int root;
	CentroidDecomposition(int n):
		T(n)
		, sz(n)
		, P(n, -1)
		, block(n)
		, rank(n)
		, root(0)
		, dist(18, vector<int>(n))
		, res(n)
	{}
	void addEdge(int a, int b) {
		T[a].emplace_back(b);
		T[b].emplace_back(a);
	}
	bool valid(int x, int p) {
		return x != p and not block[x];
	}
	int dfs(int x, int p=-1) {
		sz[x] = 1;
		for (int v : T[x])
			if (valid(v, p))
				sz[x] += dfs(v, x);
		return sz[x];
	}
	int get_centroid(int x, int p, int n) {
		for (int v : T[x])
			if (valid(v, p) and sz[v] > n>>1)
				return get_centroid(v, x, n);
		return x;
	}
	void calc_dist(int x, int r, int p=-1, int h=0) {
		dist[r][x] = h;
		for (int v : T[x])
			if (valid(v, p))
				calc_dist(v, r, x, h+1);
	}
	void decompose(int x, int p=-1, int r=0) {
		int n = dfs(x);
		int cen = get_centroid(x, -1, n);
		calc_dist(cen, r);
		P[cen] = p; 
		block[cen] = 1; 
		rank[cen] = r;
		for (auto v : T[cen]) {
			if (block[v]) continue;
			decompose(v, cen, r+1);
		}
	}
	int query(int x) {
		int ans = inf, root = x;
		while (root != -1) {
			if (not res[root].empty())
				ans = min(ans, dist[rank[root]][x] + *res[root].begin());
			root = P[root];
		}
		return ans;
	}
	void update(int x) {
		int root = x;
		while (root != -1) {
			res[root].insert(dist[rank[root]][x]);
			root = P[root];
		}
	}
	void remove(int x) {
		int root = x;
		while (root != -1) {
			res[root].erase(res[root].lower_bound(dist[rank[root]][x]));
			root = P[root];
		}
	}
};

int main() {
	int n;
	scanf("%d", &n);
	CentroidDecomposition solver(n);
	for (int i = 1; i <= n-1; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);
		solver.addEdge(a-1, b-1);
	}
	solver.decompose(0);
	vector<int> color(n);
	int q;
	scanf("%d", &q);
	while (q--) {
		int type, x;
		scanf("%d %d", &type, &x);
		x -= 1;
		if (type == 0) {
			if (not color[x]) {
				solver.update(x);
			} else {
				solver.remove(x);
			}
			color[x] ^= 1;
		} else {
			int ans = solver.query(x);
			if (ans == inf) puts("-1");
			else printf("%d\n", ans);
		}
	}
	return 0;
}