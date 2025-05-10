#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e4 + 10;
long long dis[MAXN];
long long dp[MAXN];
typedef pair<long long, int> ii;
vector<ii> adj[MAXN];

long long dijkstra(int src, int snk) {
	priority_queue<ii, vector<ii>, greater<ii> > Q;

	memset(dis, 1, sizeof dis);
	Q.push({0ll, src});
	dis[src] = 0;
	dp[src] = 1;
	while (not Q.empty()) {
		auto q = Q.top(); Q.pop();
		int v = q.second;
		long long w = q.first;

		if (w == dis[v]) {
			for (auto s : adj[v]) {
				if (w + s.second < dis[s.first]) {
					dp[s.first] = dp[v];
					Q.push({dis[s.first] = w + s.second, s.first});
				} else if (w + s.second == dis[s.first]) {
					dp[s.first] += dp[v];
				}
			}
		}

	}
	return dp[snk];
}


int main() {

	int v, e;
	scanf("%d %d", &v, &e);
	for (int i = 0; i < e; ++i) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		adj[a].push_back({b, c});	
	}	

	int s, t;
	scanf("%d %d", &s, &t);
	cout << dijkstra(s, t) << endl;

	return 0;
}