/**
 *  @author Miguel Mini
 *  @tag dfs, dp, lca_trick
 *  @idea:
 *      - we can make simple dp
 *
 *        dp[x][i] = max(dp[x][i - j] + dp[v][j])
 *
 *      where we update with children nodes.
 *
 *      - this dp is amortized to O(nm), see:
 *      https://codeforces.com/blog/entry/63257
**/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
int dp[maxn][510];
vector<int> g[maxn];
int c[maxn];
int sz[maxn];
int n, m;
void dfs(int x) {
	sz[x] = 0;
	for (int i = 1; i <= m; ++i) dp[x][i] = -1e9;
	for (int v : g[x]) {
		dfs(v);
		for (int i = min(m, sz[x]+sz[v]); i >= 1; --i) {
			for (int j = max(1, i-sz[x]); j <= min(i, sz[v]); ++j) {
				dp[x][i] = max(dp[x][i], dp[x][i-j] + dp[v][j]);
			}
		}
		sz[x] += sz[v];
	}
	sz[x] += 1;
	dp[x][1] = max(dp[x][1], c[x]);
}

int main() {
	cin >> n >> m;
	int root = 0;
	for (int i = 1; i <= n; ++i) {
		int pi;
		cin >> pi >> c[i];
		if (pi == 0) root = i;
		else g[pi].push_back(i);
	}
	dfs(root);
	cout << dp[root][m] << endl;
	return 0;
}
