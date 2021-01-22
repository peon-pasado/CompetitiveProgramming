/**
 *  @author Miguel Mini
 *  @tag dp, dfs, binary_lifting, auxiliary_tree, greedy
 *  @idea:
 *
 *      - note that if two nodes have the same color, then no 
 *      edges can be cut on the path that connects them.
 *
 *      - fixed a color, and ordering all the nodes with the order
 *      in which you discover a node in a dfs, then the union of 
 *      all the pairs of paths between those nodes is the union
 *      of the paths between consecutive pairs in that order.
 *  
 *      - We can divide each of these paths in the lca and increase
 *      1 to the bottom node and -1 to the top node, this can be done
 *      offline and endpoints of edges with sum > 0.
 *
 *      - the final answer is the number of leaves in reduced graph.
 *
**/


#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 5e5 + 10;
vector<int> g[maxn];
vector<int> color[maxn];
const int maxlog = 18;
int st[maxn][maxlog];
int lo[maxn], h[maxn];
int T;
 
void dfs(int x, int p=-1) {
	lo[x] = T++;
	h[x] = (~p ? h[p] + 1 : 0);
	st[x][0] = (~p ? p : x);
	for (int k = 1; k < maxlog; ++k) {
		st[x][k] = st[st[x][k-1]][k-1];
	}
	for (int v : g[x]) {
		if (v == p) continue;
		dfs(v, x);
	}
}
 
int lca(int x, int y) {
	if (h[x] > h[y]) swap(x, y);
	for (int i = maxlog-1; i >= 0; --i) {
		if (h[st[y][i]] >= h[x]) {
			y = st[y][i];
		}
	}
	if (x == y) return x;
	for (int i = maxlog-1; i >= 0; --i) {
		if (st[x][i] != st[y][i]) {
			x = st[x][i];
			y = st[y][i];
		}
	}
	return st[x][0];
}
 
int link[maxn];
int rnk[maxn];
 
int get(int x) {
	return x == link[x] ? x : link[x] = get(link[x]);
}
 
void merge(int x, int y) {
	x = get(x);
	y = get(y);
	if (x == y) return;
	if (rnk[x] < rnk[y]) swap(x, y);
	rnk[x] += rnk[x] == rnk[y];
	link[y] = x;
}
 
vector<pair<int, int>> edges;
int dp[maxn], deg[maxn];
void dfs_in_out(int x, int p=-1) {
	for (int v : g[x]) {
		if (v == p) continue;
		dfs_in_out(v, x);
		dp[x] += dp[v];
	}
	if (~p) {
		if (dp[x] == 0) {
			edges.push_back({x, p});
		} else {
			merge(x, p);
		}
	}
}
 
int main() {
	int n, k;
	cin >> n >> k; 
	for (int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	for (int i = 1; i <= n; ++i) {
		int d;
		cin >> d;
		color[d].push_back(i);
	}
	dfs(1);
	for (int d = 1; d <= k; ++d) {
		sort(color[d].begin(), color[d].end(), [&](int u, int v) {
			return lo[u] < lo[v];	
		});
		for (int j = 1; j < color[d].size(); ++j) {
			int u = color[d][j-1], v = color[d][j];
			int t = lca(u, v);
			dp[u] += 1;
			dp[v] += 1;
			dp[t] -= 2;
		}
	}
	for (int i = 1; i <= n; ++i) {
		link[i] = i;
		rnk[i] = 0;
	}
	dfs_in_out(1);
	for (auto e : edges) {
		int u = e.first, v = e.second;
		deg[get(u)] += 1;
		deg[get(v)] += 1;
	}
	int leaves = 0;
	for (int i = 1; i <= n; ++i) {
		if (deg[i] == 1 && get(i) == i) {
			leaves += 1;
		}	
	}
	cout << (leaves + 1) / 2 << endl;
	return 0;
}
