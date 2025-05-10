#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e6 + 10;
bool vis[maxN];
vector<pair<int, int>> g[maxN], gt[maxN], g2[maxN];
vector<int> topo;
int n;

void dfs(int x) {
	vis[x] = 1;
	for (auto node : g[x]) {
		if (not vis[node.first]) {
			dfs(node.first);
		}
	}
	topo.emplace_back(x);
}

long long calc(int x) {
	int lo = 0, hi = 2e4;
	while (lo < hi) {
		int mid = lo + (hi - lo + 1) / 2;
		if (mid *1ll* (mid + 1)  <= x + x) lo = mid;
		else hi = mid-1;
	}
	return x *1ll * (lo + 1) - lo *1ll* (lo + 1) * (lo + 2) / 6;
}

int color[maxN];
long long sum[maxN];
void dfs2(int x, int c) {
	vis[x] = 1;
	color[x] = c;
	for (auto node : gt[x]) {
		if (not vis[node.first]) {
			dfs2(node.first, c);
		}
	}
}

long long dp[maxN];
void dfs3(int x) {
	vis[x] = 1;
	dp[x] = 0;
	for (auto v : g2[x]) {
		if (not vis[v.first]) {		
			dfs3(v.first);	
		}	
		dp[x] = max(dp[x], dp[v.first] + v.second);
	}
	dp[x] += sum[x];
}

int main() {
	int m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		g[u].push_back({v, w});
		gt[v].push_back({u, w});
	}
	for (int i = 1; i <= n; ++i) {
		if (not vis[i]) {
			dfs(i);
		}
	}
	reverse(begin(topo), end(topo));
	memset(vis, 0, sizeof vis);
	int t = 1;
	for (int v : topo) {
		if (not vis[v]) {
			dfs2(v, t++);
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (auto v : g[i]) {
			if (color[i] == color[v.first]) {
				sum[color[i]] += calc(v.second);
			} else {
				g2[color[i]].push_back({color[v.first], v.second});
			}
		}
	}
	memset(vis, 0, sizeof vis);
	int s;
	scanf("%d", &s);
	dfs3(color[s]);
	printf("%lld\n", dp[color[s]]);
	return 0;
}