/**
 * @author Miguel Mini
 * @tag number_theory, max_flow
 * @idea
 *      - we can erase two blocks
 *      of consecutive 1s in three types
 *      of actions.
 * 
 *      - the main idea is that erase
 *      mare that two blocks can be
 *      decompose in erasing 1 or 2
 *      blocks.
 * 
 *      - a block 111111...100 can 
 *      be transform in 1000000...010.
 *  
 *      - with the last transform answer
 *      is obtained be erasing 1/2 blocks.
 * 
 * 
 *      - if |i - j| is prime > 2: answer 1
 *      - if |i - j| is even: answer 2
 *      - in other case: answer 3
 * 
 *      - we can match odd/even with prime
 *      distance.
 * 
 *      - match even and odd with pairs
 *      and cost 2.
 * 
 *      - if are two o one no matched ans + 3.
 * 
 *      - we can match elements with prime
 *      distance with a bipartite matching.
 * 
 * @complexity O(n^2.5 + max(x))
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

	void addEdge(int a, int b, int cap) {
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

const int maxn = 1e7 + 10;
bool arr[maxn];
bool comp[maxn];
vector<int> prime;

void sieve() {
    comp[1] = 1;
    for (int i = 2; i < maxn; ++i) {
        if (!comp[i]) prime.push_back(i);
        for (int p : prime) {
            if (p * i >= maxn) break;
            comp[p * i] = 1;
            if (i % p == 0) break;
        }
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        arr[x] = 1;
    }
    vector<int> temp[2];
    for (int i = 1; i < maxn; ++i) {
        if (arr[i] != arr[i-1]) temp[i&1].push_back(i); 
    }
    sieve();
    int m = temp[0].size() + temp[1].size();
    Dinic solver(m + 2);
    int s = m, t = m+1;
    for (int i = 0; i < temp[0].size(); ++i) 
        for (int j = 0; j < temp[1].size(); ++j)
            if (!comp[abs(temp[0][i] - temp[1][j])]) {
                solver.addEdge(i, temp[0].size() + j, 1);
            }
    for (int i = 0; i < temp[0].size(); ++i) solver.addEdge(s, i, 1);
    for (int i = 0; i < temp[1].size(); ++i) solver.addEdge(temp[0].size() + i, t, 1);        
    int k = solver.solve(s, t);
    int me = temp[0].size();    
    int mo = temp[1].size();
    int ans = k + 2 * ((me-k)/2 + (mo-k)/2) + 3 * (((me-k)&1) || ((mo-k)&1));
    cout << ans << '\n'; 
    return 0;
}