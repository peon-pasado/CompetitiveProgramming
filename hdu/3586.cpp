#include <iostream>
#include <vector>
using namespace std;

const int maxn = 1010;
const int inf = 1e9;
using ii = pair<int, int>;
vector<ii> g[maxn];

int dfs(int x, int p, int m) {
	int ans = 0;
	for (auto edge : g[x]) {
		if (edge.first == p) continue;
		ans += min(edge.second <= m ? edge.second : inf, dfs(edge.first, x, m)); 
		ans = min(ans, inf);
	}
	if (x > 1 && g[x].size() == 1) ans = inf;
	return ans;
}

int main() {
	int n, m;
	while (cin >> n >> m, n+m) {
		for (int i = 1; i <= n; ++i) {
			g[i].clear();
		}
		for (int i = 0; i < n-1; ++i) {
			int a, b, w;
			cin >> a >> b >> w;
			g[a].push_back({b, w});
			g[b].push_back({a, w});
		}
		int lo = 0, hi = 1000;
		while (lo < hi) {
			int mid = (lo + hi) / 2;
			if (dfs(1, 0, mid) > m) lo = mid+1;
			else hi = mid;
		}
		if (dfs(1, 0, lo) <= m) cout << lo << '\n';
		else cout << -1 << '\n';
	}
	return 0;
}