/**
 * @author Miguel Mini
 * @tag max_flow, closure
 * @idea
 *      - we can model the problem 
 *      as the closure problem
 * 
 *      - if i is selected we force
 *      d * i with an edge (i, d*i, inf).
 * 
 *      - if value of i is positive 
 *      we benefit if we dont take it
 *      and with -a[i] in other case.
 *  
 *      - We can rebuild the solution by
 *      analyzing the network, but it is 
 *      easier if we sum that elements are 
 *      not reachable from the source 
 *      after the cut.
 * 
 * @complexity O(n \log n \ sqrt(n))
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

bool vis[110];
void dfs(int x, Dinic& s) {
	vis[x] = 1;
	for (auto e : s.g[x]) {
		if (e.cap - e.flow > 0 && !vis[e.to]) {
			dfs(e.to, s);
		}
	}
}

int main() {
	int n;
	cin >> n;
	Dinic solver(n + 2);
	int s = 0, t = n+1;
	vector<int> a(n+1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		if (a[i] >= 0) solver.add_edge(i, t, a[i]);
		else solver.add_edge(s, i, -a[i]);
		for (int j = 2*i; j <= n; j += i) {
			solver.add_edge(i, j, inf);
		}
	}
	solver.solve(s, t);
	dfs(s, solver);
	ll ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (!vis[i]) ans += a[i];
	}
	cout << ans << endl;
	return 0;
}