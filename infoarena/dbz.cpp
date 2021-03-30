/**
 * @author Miguel Mini
 * @tag dijkstra
 * @idea
 *      - basic idea:
 * 
 *          - build dijkstra tree 
 *          for each node i
 * 
 *          - for edge (i, v) with
 *          parent[v] != i, answer is:
 *          
 *              dist[v] + (i, v).w
 * 
 *          - for other edges (u, v)
 *          with lca(u, v) == i, answer
 *          is:
 *      
 *              dist[u] + dist[v] + (u, v).w
 * 
 *          - complexity: O(nmlogn)
 * 
 *      - better idea (best constant):
 *
 *          - for second type of edges
 *          we can associate each node 
 *          with a neighbor of i in the 
 *          dijkstra tree.
 * 
 *          - modified relaxation:
 * 
 *              if dist[q] + (q, u).w < dist[u]
 *                  class[u] = q==i ? u : class[q];
 *                  dist[u] = dist[q] + (q, u).w
 *                  Q.push(make_pair(dist[u], u))
 * 
 *          - lca(u, v) == i <-> class[u] != class[v].
 * 
 * @complexity O(nmlogn)
 */ 

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1510;
vector<pair<int, int>> g[maxn];
int dist[maxn];
int p[maxn];

int main() {
    freopen("dbz.in", "r", stdin);
    freopen("dbz.out", "w", stdout);
	int n, m;
	scanf("%d%d", &n, &m);
	const int inf = 2e9;
	for (int i = 0; i < m; ++i) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		g[a].emplace_back(b, c);
		g[b].emplace_back(a, c);
	}
	for (int i = 1; i <= n; ++i) {
		using ii = pair<int, int>;
		priority_queue<ii, vector<ii>, greater<ii>> Q;
		for (int j = 1; j <= n; ++j) dist[j] = inf;
		for (int j = 1; j <= n; ++j) p[j] = -1;
		Q.emplace(dist[i] = 0, i);
		while (!Q.empty()) {
			auto q = Q.top(); Q.pop();
			if (dist[q.second] != q.first) continue;
			for (auto e : g[q.second]) {
				if (q.first + e.second < dist[e.first]) {
				    if (q.second == i) p[e.first] = e.first;
					else p[e.first] = p[q.second];
					Q.emplace(dist[e.first] = q.first+e.second, e.first);
				}
			}
		}
		int ans = inf;
		for (int j = 1; j <= n; ++j) {
		    if (j == i) {
		        for (auto e : g[i]) {
		            if (p[e.first] == e.first) continue;
		            ans = min(ans, dist[e.first] + e.second);
		        }
		        continue;
		    }
		    if (dist[j] == inf) continue;
		    for (auto e : g[j]) {
		        if (e.first == i) continue;
		        if (dist[e.first] == inf) continue;
		        if (p[j] == p[e.first]) continue;
		        ans = min(ans, dist[j] + dist[e.first] + e.second);
		    }
		}
		if (ans == inf) printf("-1 ");
		else printf("%d ", ans);
	}
	puts("");
	return 0;
}