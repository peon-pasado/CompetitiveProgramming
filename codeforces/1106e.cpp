#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e5 + 2;
long long memo[maxN][201];
bool vis[maxN][201];
pair<int, int> nxt[maxN];
struct Node {
	int id, d, w; 
};
vector<Node> q[maxN];
int n, m, k;

long long dp(int pos, int w) {
	if (pos == n+1) return 0;
	if (vis[pos][w]) return memo[pos][w];
	vis[pos][w] = 1;
	long long &ans = memo[pos][w] = 1e18;
	if (nxt[pos].second != -1) {
		ans = min(ans, dp(nxt[pos].second, w) + nxt[pos].first);
	} else {
		ans = min(ans, dp(pos+1, w));
	}
	if (w > 0) {
		ans = min(ans, dp(pos+1, w-1));
	}
	return ans;
}

int main() {
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= k; ++i) {
		int s, t, d, w;
		scanf("%d %d %d %d", &s, &t, &d, &w);
		q[s].push_back({i, d+1, w});
		q[t+1].push_back({-i, d+1, w});
	}
	multiset<pair<int, int>, greater<pair<int, int>>> s;
	for (int i = 1; i <= n; ++i) {
		for (auto e : q[i]) {
			if (e.id < 0) {
				s.erase(s.lower_bound({e.w, e.d}));
			} else {
				s.insert({e.w, e.d});
			}
		}
		nxt[i] = s.empty() ? make_pair(-1, -1) : *(s.begin());
	}
	printf("%lld\n", dp(1, m));
	return 0;
}