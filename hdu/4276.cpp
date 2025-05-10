#include <iostream>
#include <vector>
using namespace std;

const int maxn = 110;
const int maxT = 510;
vector<pair<int,int>> g[maxn];
bool vis[maxn];
int n, T;
int c[maxn];

bool dfs_path(int x, int p) {
	vis[x] = 1;
	if (x == n) return 1;
	for (int i = 0; i < g[x].size(); ++i) {
		int v = g[x][i].first;
		if (v == p) continue;
		if (dfs_path(v, x)) return 1;
	}
	vis[x] = 0;
	return 0;
}

int dp[maxn][maxT];
void dfs(int x, int p) {
	if (x == 1) {
		for (int i = 0; i <= T; ++i) {
			dp[x][i] = c[x];
		}
	}
	int nxt = -1, nxt_w;
	for (int i = 0; i < g[x].size(); ++i) {
		int v = g[x][i].first;
		int ti = g[x][i].second;
		if (v == p) continue;
		int w = 2 * ti;
		if (vis[v]) {
			nxt = v;
			nxt_w = w / 2;
			continue;
		}	
		for (int j = 0; j <= T; ++j) {
			dp[v][j] = j >= w ? dp[x][j-w] + c[v] : -1e9;
		}
		dfs(v, x);
		for (int j = 0; j <= T; ++j) {
			dp[x][j] = max(dp[x][j], dp[v][j]);
		}
	}
	if (~nxt) {
		for (int j = 0; j <= T; ++j) {
			dp[nxt][j] = j >= nxt_w ? dp[x][j-nxt_w] + c[nxt] : -1e9;
		}
		dfs(nxt, x);
	}
}

int main() {
	while (cin >> n >> T) {
		for (int i = 1; i <= n; ++i) {
			g[i].clear();
			vis[i] = 0;
		}
		for (int i = 0; i < n-1; ++i) {
			int a, b, c;
			cin >> a >> b >> c;
			g[a].push_back({b, c});
			g[b].push_back({a, c});
		}
		for (int i = 1; i <= n; ++i) {
			cin >> c[i];
		}
		dfs_path(1, 0);
		dfs(1, 0);
		int ans = -1e9;
		for (int i = 0; i <= T; ++i) {
			ans = max(ans, dp[n][i]);
		}
		if (ans < 0) {
			cout << "Human beings die in pursuit of wealth, and birds die in pursuit of food!\n";
		} else {
			cout << ans << '\n';
		}
	}
	return 0;
}