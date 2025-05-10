#include <iostream>
#include <vector>
using namespace std;

const int maxn = 210;
const int inf = 1e8;
int dp[maxn / 2][maxn][2];
vector<int> g[maxn];
int sz[maxn];
int c[maxn];
int n, k;

void dfs(int x, int p) {
	sz[x] = 1;
	for (int i = 1; i <= k; ++i) {
		dp[x][i][0] = dp[x][i][1] = -inf;
	}
	dp[x][0][0] = dp[x][0][1] = c[x];
 	for (int t = 0; t < g[x].size(); ++t) {
		int v = g[x][t];
		if (v == p) continue;
		dfs(v, x);
		for (int i = k; i >= 1; --i) {
			for (int j = i; j >= 1; --j) {
				//cout << i << ' ' << j << '\n';
				dp[x][i][0] = max(dp[x][i][0], dp[x][i-j][1] + dp[v][j-1][0]);
				if (j >= 2) {
					dp[x][i][0] = max(dp[x][i][0], dp[x][i-j][0] + dp[v][j-2][1]);
					dp[x][i][1] = max(dp[x][i][1], dp[x][i-j][1] + dp[v][j-2][1]);
				}
				//dp[x][i][0] = max(dp[x][i][0], dp[x][i][1]);
			}
			dp[x][i][0] = max(dp[x][i][0], dp[x][i][1]);
		}
 		sz[x] += sz[v];
 	}
}


int main() {
	while (cin >> n >> k) {
		for (int i = 1; i <= n; ++i) {
			g[i].clear();
		}
		for (int i = 1; i <= n; ++i) {
			cin >> c[i];
		}
		for (int i = 0; i < n-1; ++i) {
			int a, b;
			cin >> a >> b;
			g[a].push_back(b);
			g[b].push_back(a);
		}
		dfs(1, 0);
		int ans = 0;
		for (int i = 0; i <= k; ++i) {
			ans = max(ans, dp[1][i][0]);
		}
		cout << ans << '\n';
	}
	return 0;
}