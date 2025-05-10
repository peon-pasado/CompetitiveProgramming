#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e5 + 10;
vector<int> g[maxN];
int n;
int ans = 0;

void dfs(int node, int h) {
	ans = max(ans, h);
	for (int u : g[node]) {	
		dfs(u, h+1);
	}
}

int main() {
	cin >> n;
	vector<int> root;
	for (int i = 1; i <= n; ++i) {
		int p;
		cin >> p;
		if (p == -1) {
			root.emplace_back(i);
			continue;
		}
		g[p].emplace_back(i);
	}
	for (int r : root) {
		dfs(r, 1);
	}
	cout << ans << endl;
	return 0;
}
