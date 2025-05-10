#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e4 + 20;
typedef pair<int, int> ii;
int n, m, f, s, t;
vector<ii> adj[MAXN];
long long dis[2][MAXN];
typedef pair<long long, int> lli;

long long dijkstra(int id, int src, int snk) {
	priority_queue<lli, vector<lli>, greater<lli>> Q;
	
	for (int i = 0; i < n; ++i)
		dis[id][i] = 1e12;
	dis[id][src] = 0;
 	Q.push({0, src});
	
	while(not Q.empty()) {
		auto qw = Q.top(); Q.pop();
		
		int q = qw.second;
		long long w = qw.first;

		if (w == dis[id][q]) {
			for (auto v : adj[q]) {
				if (w + v.second < dis[id][v.first]) {
					dis[id][v.first] = w + v.second;
					Q.push({dis[id][v.first], v.first});
				}
			}
		}
	}
	
	return dis[id][snk];
}


int main() {

	scanf ("%d %d %d %d %d", &n, &m, &f, &s, &t);
	for (int i = 0; i < m; ++i) {
		int u, v, c;
		scanf ("%d %d %d", &u, &v, &c);
		adj[u].push_back({v, c});
		adj[v].push_back({u, c});
	}
	
	long long ans;
	ans = dijkstra(0, s, t);
	dijkstra(1, t, s);

	for (int i = 0; i < f; ++i) {
		int u, v;
		scanf ("%d %d", &u, &v);
		ans = min(ans, dis[0][u] + dis[1][v]);		
	}	
	printf("%lld\n", ans);

	return 0;
}