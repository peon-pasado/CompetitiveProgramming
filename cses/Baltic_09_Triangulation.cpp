/**
 *  @author Miguel Mini
 *  @tag dp, dfs, binary_lifting, auxiliary_tree, geometry
 *  @idea:
 *      - notice that a triangulation has an associated 
 *      tree: connect each triangle with the adjacent triangles.
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
 *      offline and count the nodes other than the root with sum 0.
 *
 *  @complexity O(n \log n). the best is O(n).
**/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
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

int dp[maxn];
int dfs_in_out(int x, int p=-1) {
	int ans = 0;
	for (int v : g[x]) {
		if (v == p) continue;
		ans += dfs_in_out(v, x);
		dp[x] += dp[v];
	}
	if (dp[x] == 0) ans += 1;
	return ans;
}

int main() {
	int n;
	cin >> n;
	map<pair<int, int>, int> last;
	auto add_edge = [&](int i, int x, int y) {
		if (x > y) swap(x, y);
		if (!last.count({x, y})) {
			last[{x, y}] = i;
			return;
		}
		int p = last[{x, y}];
		g[i].push_back(p);
		g[p].push_back(i);
	};
	for (int i = 0; i < n - 2; ++i) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		add_edge(i, a, b);
		add_edge(i, a, c);
		add_edge(i, b, c);
		color[d].push_back(i);
	}
	dfs(0);
	for (int d = 1; d <= n; ++d) {
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
	cout << dfs_in_out(0) - 1 << endl;
	return 0;
}
