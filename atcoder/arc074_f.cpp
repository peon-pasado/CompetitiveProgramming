/**
 * @author Miguel Mini
 * @tag max_flow
 * @idea
 *      - We can model the problem as 
 *      the minimum cut of a network, 
 *      where each cell is represented 
 *      by two nodes joined by an edge 
 *      that indicates the cost of 
 *      elimination and two neighboring
 *      nodes are connected by edges of 
 *      infinite cost.
 * 
 * @complexity O(nm(n+m)sqrt(nm)) (best in practice)
 */ 

#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define trav(i, x) for (auto i : x)
#define re(x, y, z) for (int x=y; x<z; ++x)
#define eb emplace_back
#define set_to(x, v) fill(all(x), v)
using namespace std;
using ll = long long;
using vi = vector<int>;
const int inf = 1e9;
struct Dinic {
	struct Edge {
		int to, cap, flow, link;
		Edge() {}
		Edge(int to, int cap, int link, int flow=0):
			to(to), cap(cap), link(link), flow(flow) {}
	};
	vector<vector<Edge>> g;
	vi d, pt;
	
	Dinic(int n): g(n), d(n), pt(n) {}

	void add_edge(int a, int b, int cap) {
		if (a == b) return;
	  	int pa = sz(g[a]), pb = sz(g[b]);
		g[a].eb(b, cap, pb); g[b].eb(a, 0, pa);
	}

	bool bfs(int src, int snk) {
		queue<int> q({src});
		set_to(d, inf);
		d[src] = 0;
		while (!q.empty()) {
			int v = q.front(); q.pop();
			if (v == snk) return true;
			trav(e, g[v]) {
				if (e.flow >= e.cap) continue;
				if (d[e.to] > d[v] + 1) {
					d[e.to] = d[v] + 1;
					q.emplace(e.to);
				}
			}
		}
		return false;
	}

	int dfs(int x, int snk, int flow=inf) {
		if (x == snk || !flow) return flow;
		for (; pt[x] < sz(g[x]); ++pt[x]) {
			auto& e = g[x][pt[x]];
			if (d[e.to] == d[x] + 1) {
				int res = min(e.cap - e.flow, flow);
				if (int push = dfs(e.to, snk, res)) {
					e.flow += push;
					g[e.to][e.link].flow -= push;
					return push;
				}
			}
		}
		return 0;
	}

	ll solve(int s, int t) {
		ll res = 0;
		while (bfs(s, t)) {
			set_to(pt, 0);
			while (int flow = dfs(s, t)) {
				res += flow;
			}
		}
		return res;
	}
};

const int maxn = 110;
char mat[maxn][maxn];

int main() {
	int n, m;
	cin >> n >> m;
	int sx, sy;
	int tx, ty;
	for (int i = 0; i < n; ++i) {
		cin >> mat[i];
		for (int j = 0; j < m; ++j) {
			if (mat[i][j] == 'S') {
				sx = i; sy = j;
				mat[i][j] = 'o';
			}
			if (mat[i][j] == 'T') {
				tx = i; ty = j;
				mat[i][j] = 'o';
			}
		}
	}
	const int dx[] = {-1, 1, 0, 0};
	const int dy[] = {0, 0, -1, 1};
	auto in = [&](int x, int y) {
		return (x * m + y) * 2;
	};
	auto out = [&](int x, int y) {
		return (x * m + y) * 2 + 1;
	};
	auto valid = [&](int x, int y) {
		return min(x, y) >= 0 && x < n && y < m;
	};
	Dinic solver(2 * n * m);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (mat[i][j] == 'o') {
				int w = 1;
				if (i == sx && j == sy) {
					w = 1e9;
				}
				if (i == tx && j == ty) {
					w = 1e9;
				}
				solver.add_edge(in(i, j), out(i, j), w);
				for (int k = 0; k < 4; ++k) {
					for (int d = 1; d < 100; ++d) {
						int nx = i + dx[k] * d;
						int ny = j + dy[k] * d;
						if (!valid(nx, ny)) break;
						solver.add_edge(out(i, j), in(nx, ny), 1e9);
					}
				}
			}
		}
	}
	int ans = solver.solve(in(sx, sy), out(tx, ty));
	if (ans > n * m) cout << -1 << '\n';
	else cout << ans << '\n';
	return 0;
}