#include <bits/stdc++.h>
using namespace std;
const int maxN = 5;
bool vis[maxN];
multiset<int> g[maxN];
int dist[maxN][maxN];
int sum[maxN];
int deg[maxN];

int dfs(int x) {
	vis[x] = 1;
	int mask = (1<<x);
	for (auto e : g[x]) {
		if (not vis[e]) {
			mask |= dfs(e);
		}
	}
	return mask;
}

int n;

int main() {
	cin >> n;
	memset(dist, 1, sizeof dist);
	for (int i = 1; i <= n; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		a -= 1;
		c -= 1;			
		g[a].insert(c);
		g[c].insert(a);
		dist[a][c] = dist[c][a] = min(dist[a][c], b); 
		sum[a] += b;
		sum[c] += b;
		deg[c] += 1;
		deg[a] += 1;
	}

	int ans = INT_MIN;
	for (int mask = 0; mask < (1<<16); ++mask) {
		int lmask = 0;
		for (int i = 0; i < 16; ++i) {
			if (mask & (1<<i)) {
				int a = i / 4;
				int b = i % 4;
				if (a > b) continue;
				if (g[a].count(b)) {
					lmask |= (1<<i);
					deg[a] -= 1;
					deg[b] -= 1;
					g[a].erase(g[a].lower_bound(b));
					g[b].erase(g[b].lower_bound(a));
					sum[a] -= dist[a][b];
					sum[b] -= dist[a][b];
				}
			}
		}
		memset(vis, 0, sizeof vis);
		for (int i = 0; i < 4; ++i) {
			if (not vis[i]) {
				int mm = dfs(i);
				int d = 0;
				int lans = 0;
				for (int j = 0; j < 4; ++j) {
					if (mm & (1 << j)) {
						d += (deg[j]&1);
						lans += sum[j];
					}
				}
				if (d <= 2) {
					ans = max(ans, lans);
				}
			}
		}

		for (int i = 0; i < 16; ++i) {
			if (lmask & (1<<i)) {
				int a = i / 4;
				int b = i % 4;
				deg[a] += 1;
				deg[b] += 1;
				g[a].insert(b);
				g[b].insert(a);
				sum[a] += dist[a][b];
				sum[b] += dist[a][b];
			}
		}	
	}
	cout << ans/2 << endl;
	return 0;
}