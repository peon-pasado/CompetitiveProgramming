/**
 * @author Miguel Mini
 * @tag geometry, sorting
 * @idea
 *      - we can encode every
 *      square with the center 
 *      and the slope of its 
 *      diagonals (we can chose
 *      one of them).
 * 
 *      - we can use a diagonal
 *      and find the other.
 * 
 * @complexity O(n^2 \log n)
 */ 

#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("patrate3.in", "r", stdin);
    freopen("patrate3.out", "w", stdout);
	int n;
	scanf("%d", &n);
	vector<pair<int, int>> p(n);
	auto get = []() {
		long double x;
		scanf("%Lf", &x);
		return (int)round(x * 10000);
	};
	for (int i = 0; i < n; ++i) {
		p[i].first = get();
		p[i].second = get();
	}
	using ii = pair<int, int>;
	vector<tuple<int, int, int, int>> v;
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			int x = p[i].first + p[j].first;
			int y = p[i].second + p[j].second;
			int vx = p[i].first - p[j].first;
			int vy = p[i].second - p[j].second;
			if (vx < 0 || (vx == 0 && vy < 0)) {
			  vx = -vx;
			  vy = -vy;
			} 
			int tvx = -vy;
			int tvy = vx;
			if (tvx < 0 || (tvx == 0 && tvy < 0)) {
			  tvx = -tvx;
			  tvy = -tvy;
			}
			if (ii(vx, vy) < ii(tvx, tvy)) {
			  v.emplace_back(vx, vy, x, y);
			} else {
		        v.emplace_back(tvx, tvy, x, y);
			}
		}
	}
	sort(v.begin(), v.end());
	long long ans = 0;
	for (int i = 0; i < v.size();) {
		int j = i;
		while (j < v.size() && v[i] == v[j]) j++;
		ans += (j - i) *1ll* (j - i - 1) / 2;
		i = j;
	}
	printf("%lld\n", ans);
	return 0;
}