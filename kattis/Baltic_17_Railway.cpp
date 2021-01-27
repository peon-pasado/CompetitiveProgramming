/**
 *  @author Miguel Mini
 *  @tag dfs, auxiliary_tree, dp, timestamp, stack, sorting
 *  @idea:
 *      - for every deputy minister we can make an auxiliary tree. 
 *
 *      - add 1/-1 for every edge in auxiliary tree.
 *
 *      - run dfs in/out to update values (offline).
 *
 *  @complexity O((n + s) \log n + m)
**/


#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
using namespace std;
 
const int maxn = 1e5 + 10;
struct Edge {	
	int v, id;
};
vector<Edge> g[maxn];
vector<int> color[maxn];
const int maxlog = 18;
int st[maxn][maxlog];
int lo[maxn], hi[maxn];
int h[maxn];
int T, k;
 
void dfs(int x, int p=-1) {
	lo[x] = T++;
	h[x] = (~p ? h[p] + 1 : 0);
	st[x][0] = (~p ? p : x);
	for (int k = 1; k < maxlog; ++k) {
		st[x][k] = st[st[x][k-1]][k-1];
	}
	for (auto edge : g[x]) {
		if (edge.v == p) continue;
		dfs(edge.v, x);
	}
	hi[x] = T++;
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
void make_auxiliary_tree(vector<int> nodes) {
	vector<int> new_nodes(nodes);
	auto cmp = [&](int u, int v) { 
		return lo[u] < lo[v];
	};
	sort(all(nodes), cmp);
	for (int i = 1; i < nodes.size(); ++i) {
		new_nodes.push_back(lca(nodes[i], nodes[i-1]));		
	}
	sort(all(new_nodes), cmp);
	new_nodes.erase(unique(all(new_nodes)), new_nodes.end());
	stack<int> s;
	for (int v : new_nodes) {
		while (!s.empty() && hi[s.top()] < lo[v]) s.pop();
		if (!s.empty()) {
			dp[v] += 1;
			dp[s.top()] -= 1;
		}
		s.push(v);
	}
}

vector<int> edge_list;
void dfs_in_out(int x, int p=-1, int id=-1) {
	for (auto edge : g[x]) {
		if (edge.v == p) continue;
		dfs_in_out(edge.v, x, edge.id);
		dp[x] += dp[edge.v];
	}
	if (~p && dp[x] >= k) {
		edge_list.push_back(id);
	}
}

int main() {
	int n, m;
	cin >> n >> m >> k;
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].push_back({v, i});
		g[v].push_back({u, i});
	}
	dfs(1);
	for (int i = 0; i < m; ++i) {
		int s;
		cin >> s;
		vector<int> nodes(s);
		for (int& x : nodes) cin >> x;
		make_auxiliary_tree(nodes);
	}
	dfs_in_out(1);
	sort(all(edge_list));
	int l = edge_list.size();
	cout << l << '\n';
	for (int i = 0; i < l; ++i) {
		cout << edge_list[i] << " \n"[i+1==l];
	}
	return 0;
}
