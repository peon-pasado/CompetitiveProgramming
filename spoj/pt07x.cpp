/** just for fun xD **/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
bool C[maxn];
vector<int> g[maxn];
int n;
 
struct BipartiteMatcher {
	vector<vector<int>> g;
	vector<int> L, R;
	vector<bool> vis;
	BipartiteMatcher(int n, int m) {
		g.resize(n);
		L.resize(n, -1);
		R.resize(m, -1);
		vis.resize(n);
	}
	
	void addEdge(int a, int b) {
		g[a].push_back(b);
	}
	
	bool match(int x) {
		if (vis[x]) return 0;
		vis[x] = 1;
		for (int v : g[x]) 
			if (R[v] == -1) 
				return R[L[x] = v] = x, 1;
		for (int v : g[x])
			if (match(R[v])) 
				return R[L[x] = v] = x, 1;
		return 0;
	}
 
	int solve() {
		int cnt = 1;
		while (cnt--) {
			fill(begin(vis), end(vis), 0);
			for (int i = 0; i < L.size(); ++i) {
				cnt |= L[i] == -1 and match(i);
			}
		}
		int res = 0;
		for (int i = 0; i < L.size(); ++i) {
			res += L[i] != -1;
		}
		return res;
	}
} BM(1e5, 1e5);
 
void dfs(int x, int p, int c) {
	C[x] = c;
	for (int v : g[x]) {
		if (v == p) continue;
		dfs(v, x, c^1);
	}
	if (C[x] == 0)
		for (int v : g[x])
			BM.addEdge(x, v);
}
 
int main() {
	cin >> n;
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		u--; v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(0, 0, 0);
	cout << BM.solve() << endl;
	return 0;
} 