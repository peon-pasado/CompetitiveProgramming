#include <iostream>
#include <vector>
using namespace std;

const int maxn = 160;
const int inf = 1e5;
vector<int> g[maxn];
int sz[maxn];
int dp[maxn][maxn];
int n, k;

void dfs(int x, int p) {
	sz[x] = 1;
	for (int i = 2; i <= k; ++i) {
		dp[x][i] = inf;
	}
	dp[x][1] = 0;
	for (int t = 0; t < g[x].size(); ++t) {
		int v = g[x][t];
		if (v == p) continue;
		dfs(v, x);
		int temp[k + 1];
		for (int i = 1; i <= k; ++i) temp[i] = dp[x][i] + 1;
		for (int i = min(k, sz[x]+sz[v]); i >= 1; --i) {
			for (int j = min(i-1, sz[v]); j >= max(1, i-sz[x]); --j) {
				temp[i] = min(temp[i], dp[x][i-j] + dp[v][j]);
			}			
		}
		for (int i = 0; i <= k; ++i) dp[x][i] = temp[i];
		sz[x] += sz[v];
	}
}

int main() {
	cin >> n >> k;
	for (int i = 0; i < n-1; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(1, 0);
	int ans = dp[1][k];
	for (int i = 2; i <= n; ++i) ans = min(ans, dp[i][k] + 1);
	cout << ans << '\n';
	return 0;
}