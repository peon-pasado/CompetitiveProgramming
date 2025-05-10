#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
int dis[MAXN];
int dp[MAXN];
int t[MAXN];
int n, m;
typedef pair<int, int> ii;
vector<ii> adj[MAXN];


bool dijkstra(int src, int snk) {
	priority_queue<ii, vector<ii>, greater<ii>> Q;
	Q.push({0, src});
	for (int i = 1; i <= n; ++i)
		dis[i] = 1<<30;

	dis[src] = 0;
	dp[src] = t[src];

	while (not Q.empty()) {
		auto q = Q.top();
		Q.pop();
	
		int u = q.second;
		int w = q.first;

		if (dis[u] == w) {
			for (auto v : adj[u]) {
				if (w + v.second < dis[v.first]) {
					dis[v.first] = w + v.second;
					dp[v.first] = dp[u] + t[v.first];
					Q.push({dis[v.first], v.first});
				} else if (w + v.second == dis[v.first]) {
					dp[v.first] = max(dp[v.first], dp[u] + t[v.first]);
				}
			}
		}
	}

	if (dis[snk] == (1<<30)) return 0;
	return 1;
}


int main() {

	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", t+i);	
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		int a, b, w;
		scanf ("%d %d %d", &a, &b, &w);
		adj[a].push_back({b, w});
		adj[b].push_back({a, w});
	}

	if(dijkstra(1, n)) printf("%d %d\n", dis[n], dp[n]);
	else printf("impossible\n");

	return 0;
}