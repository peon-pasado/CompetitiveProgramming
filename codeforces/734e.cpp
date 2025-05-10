#include <bits/stdc++.h>
using namespace std;
const int maxN = 2e5 + 10;
int n;
vector<int> g[maxN], h[maxN];
int color[maxN];
int key[maxN];
int T;

void dfs(int x, int p, int t) {
	key[x] = t;
	for (int v : g[x]) {
		if (v != p) {
			if (color[v] == color[x]) {
				dfs(v, x, t);
			} else {
				dfs(v, x, T += 1);
				h[key[x]].push_back(key[v]);
				h[key[v]].push_back(key[x]);
			}
		}
	}
}

pair<int, int> dfs2(int x, int p = 0) {
	pair<int, int> ans = {0, x};
	for (int v : h[x]) {
		if (v != p) {
			auto q = dfs2(v, x);
			q.first += 1;
			ans = max(ans, q);
		}
	}
	return ans;
}


int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> color[i];
	}
	for (int i = 0; i+1 < n; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	dfs(1, 0, T += 1);
	auto q = dfs2(1);
	q = dfs2(q.second);
	cout << (q.first + 1) / 2 << endl;
	return 0;
}