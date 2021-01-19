/**
 *  @name Miguel Mini
 *  @tag dijkstra, amortized
 *  @idea
 *      - the number of edges from a especific position
 *      is 2 * n / p.
 *
 *      - note that for each b % p, the total number of
 *      edges is at most 2 * n / p. for b1 < b2, we dont
 *      need edges from b2 to i < b1 or edges from
 *      b1 to i > b2.
 *
 *      - therefor for each p, the number of distinct b % p
 *      is p, such that the worst case is take ps (with distinct b):
 *        
 *          {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, ...}
 *
 *      with cost n/1 + 2 * n/2 + 3 * n/3 + 4 * n/4 + ... t_q * n/q
 *      and t_1 + t_2 + ... t_q <= m, then q = O(sqrt(m)). finally    
 *      the number of edges is O(n sqrt(m)).
 *
 *      - solve with a dijkstra O(nsqrt(m)log(n) + n).
 *
**/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e4 + 10;
set<int> pos[maxn];
vector<pair<int, int>> g[maxn];
using ll = long long;
ll d[maxn];

ll dijkstra(int src, int snk) {
	memset(d, 1, sizeof d);
	d[src] = 0;
	using pii = pair<ll, int>;
	priority_queue<pii, vector<pii>, greater<pii>> Q;
	Q.push({0, src});
	while (!Q.empty()) {
		auto q = Q.top(); Q.pop();
		if (q.second == snk) return q.first;
		if (q.first != d[q.second]) continue;
		for (auto e : g[q.second]) {
			ll temp = q.first + e.second;
			if (temp < d[e.first]) {
				d[e.first] = temp;
				Q.push({temp, e.first});
			}
		}
	}
	return -1;
}

int main() {
	int n, m;
	cin >> n >> m;
	set<pair<int, int>> t;
	int x = -1, y = -1;
	for (int i = 0; i < m; ++i) {
		int b, p;
		cin >> b >> p;
		t.insert({p, b});
		pos[b].insert(p);
		if (x == -1) x = b;
		else if (y == -1) y = b;
	}
	auto same = [](int b, int p) {
		return !pos[b].empty() && pos[b].count(p);	
	};
	for (auto q : t) {
		for (int i = 1; ; ++i) {
			int temp = q.second + i * q.first;
			if (temp >= n) break;
			g[q.second].emplace_back(temp, i);
			if (same(temp, q.first)) break;
		}
		for (int i = 1; ; ++i) {
			int temp = q.second - i * q.first;
			if (temp < 0) break;
			g[q.second].emplace_back(temp, i);
			if (same(temp, q.first)) break;
		}
	}
	cout << dijkstra(x, y) << endl;
	return 0;
}
