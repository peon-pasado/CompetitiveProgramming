#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int n, q;
vector<pair<int, int>> P, Q;
int ft[maxn];
int L[maxn], R[maxn];

void update(int pos, int v) {
	while (pos < maxn) {
		ft[pos] += v;
		pos += pos&-pos;
	}
}
int query(int pos) {
	int ans = 0;
	while (pos > 0) {
		ans += ft[pos];
		pos -= pos&-pos;
	}
	return ans;
}
int ans[maxn];
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int x;
		cin >> x;
		P.push_back({x, i});
	}
	sort(begin(P), end(P));
	cin >> q;
	for (int i = 1; i <= q; ++i) {
		int l, r, k;
		cin >> l >> r >> k;
		L[i] = l; R[i] = r;
		Q.push_back({k, i});
	}
	sort(begin(Q), end(Q));
	for (int i = 1; i <= n; ++i) {
		update(i, 1);
	}
	for (int i = 0, j = 0; i < q; ++i) {
		while (j < n and P[j].first <= Q[i].first) {
			update(P[j++].second, -1);
		}
		int id = Q[i].second;
		ans[id] = query(R[id]) - query(L[id] - 1); 
	}
	for (int i = 1; i <= q; ++i) {
		cout << ans[i] << '\n';
	}
	return 0;
}