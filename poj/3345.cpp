#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <cstring>
using namespace std;

const int maxn = 210;
int sz[maxn];
vector<int> g[maxn];
int dp[maxn][maxn];
int c[maxn];
int n, k;
int deg[maxn];

void dfs(int x) {
	sz[x] = 1;
	dp[x][1] = c[x];
	for (int i = 0; i < g[x].size(); ++i) {
		int v = g[x][i];
		dfs(v);
		for (int i = 1; i <= sz[v]; ++i) dp[x][sz[x] + i] = c[x];
		for (int i = min(k, sz[x]+sz[v]); i >= 0; --i) {
			for (int j = min(k, sz[v]); j >= 1; --j) {
				dp[x][i] = min(dp[x][i], dp[x][i-j] + dp[v][j]);
			}
		}
		sz[x] += sz[v];
	}	
}

int main() {
	string s;
	getline(cin, s);
	while (s != "#") {
		stringstream ss(s);
		ss >> n >> k;
		for (int i = 0; i <= n; ++i) {
			g[i].clear();
			deg[i] = 0;
		}
		map<string, int> id;
		int m = 0;
		for (int i = 0; i < n; ++i) {
			getline(cin, s);
			stringstream ss(s);
			int w;
			ss >> s >> w;
			if (!id.count(s)) id[s] = m++;
			int nd = id[s];
			c[nd] = w;
			while (ss >> s) {
				if (!id.count(s)) id[s] = m++;
				int nxt = id[s];
				g[nd].push_back(nxt);
				deg[nxt]++;
			}
		}
		c[n] = 2e9;
		for (int i = 0; i < n; ++i) {
			if (deg[i] == 0) {
				g[n].push_back(i);
			}
		}
		dfs(n);
		cout << dp[n][k] << '\n';
		getline(cin, s);
	}
	return 0;
}