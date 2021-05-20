/**
 * @author Miguel Mini
 * @tag binary_serach, number_theory
 * @idea
 *      - we can calculate all divisor
 *      from 1 to m in O(m \log m)
 * 
 *      - save index from i in 
 *      linked list associated to element
 *      a_i.
 * 
 *      - use binary search to find elements.
 * 
 * @complexity O(Q X^{1/3} \log (N) + max(a) \log max(a))
 */ 
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
vector<int> adj[maxn];
vector<int> d[maxn];

int main() {
	int n, q;
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i) {
		int x;
		scanf("%d", &x);
		adj[x].push_back(i);
	}
	for (int i = 1; i < maxn; ++i) {
		for (int j = i; j < maxn; j += i) {
			d[j].push_back(i);
		}
	}
	auto query = [&](int l, int r, int x)->bool {
		if (adj[x].empty()) return false;
		int lo = 0, hi = adj[x].size() - 1;
		while (lo < hi) {
			int mid = (lo + hi) / 2;
			if (adj[x][mid] < l) lo = mid+1;
			else hi = mid;
		}
		return l <= adj[x][lo] && adj[x][lo] <= r;
	};
	while (q--) {
		int l, r, x;
		cin >> l >> r >> x;
		bool ok = false;
		for (int di : d[x]) {
			if (di != x / di && query(l, r, di) && query(l, r, x / di)) {
				ok = true;
				break;
			} 
		}
		puts(ok ? "YES" : "NO");
	}
	return 0;
}