#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e5 + 10;
int o[maxN], c[maxN];
int n, m, k;
bool vis[3][maxN];
int dis[3][maxN];
vector<int> g[maxN], gt[maxN];

void bfs(int id, int v[], int n) {
	queue<int> Q;
	for (int i = 1; i <= n; ++i) {
		Q.push(v[i]);
		dis[id][v[i]] = 0;
		vis[id][v[i]] = 1;
	}
	while (not Q.empty()) {
		int q = Q.front(); Q.pop();
		if (id < 2) {
			for (int v : gt[q]) {
				if (not vis[id][v]) {
					vis[id][v] = 1;
					dis[id][v] = dis[id][q] + 1;
					Q.push(v);
				}
			}
		} else {
			for (int v : g[q]) {
				if (not vis[id][v]) {
					vis[id][v] = 1;
					dis[id][v] = dis[id][q] + 1;
					Q.push(v);
				}
			}
		}
	}
}

int main() {
	while (scanf("%d %d %d", &n, &m, &k) == 3) {
		for (int i = 1; i <= m; ++i) scanf("%d", o+i);
		for (int i = 1; i <= k; ++i) scanf("%d", c+i);
		for (int i = 1; i <= n; ++i) gt[i].clear();
		for (int i = 1; i <= n; ++i) {
			g[i].clear();
			int l; scanf("%d", &l);
			for (int j = 1; j <= l; ++j) {
				int x;
				scanf("%d", &x);
				g[i].push_back(x);
				gt[x].push_back(i);
			}
		}
		memset(vis[0], 0, sizeof vis[0]);
		bfs(0, o, m);
		memset(vis[1], 0, sizeof vis[1]);
		bfs(1, c, k);
		int id[3] = {0, 1};
		memset(vis[2], 0, sizeof vis[2]);
		bfs(2, id, 1);
		int ans = 1e9;
		for (int i = 1; i <= n; ++i) {
			if (vis[2][i] and vis[0][i] and vis[1][i]) {
				ans = min(ans, dis[2][i] + dis[1][i] + dis[0][i]);
			}
		}
		if (ans > n) puts("impossible");
		else printf("%d\n", ans);
	}
	return 0;
}