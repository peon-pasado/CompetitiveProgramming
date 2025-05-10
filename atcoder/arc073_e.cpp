/**
 * @author Miguel Mini
 * @tag greedy, sorting
 * @idea
 *      - we considere array with
 *      2n elements and:
 * 
 *          arr[2 * i] = x[i]
 *          arr[2 * i + 1] = y[i]
 * 
 *      - we can assign maximum 
 *      element as red and minimum
 *      as blue. In that case we
 *      can greedily assign:
 * 
 *           min(x[i], y[i]) to blue
 *           max(x[i], y[i]) to red
 *  
 *      - in other case suppose that
 *      maximum and minimun elements
 *      can be assign to red, then:
 * 
 *          1. we assign opossite 
 *          for minimum and maximum
 *          to blue, this pair is
 *          (l, r) with l <= r.
 * 
 *          2. if a bag has 
 *          r < min(x[i], y[i]), assign
 *          r = min(x[i], y[i]).
 * 
 *          3. if a bag has l > max(x[i], y[i]),
 *          assign l = max(x[i], y[i])
 * 
 *          4. if a bag has x or y between 
 *          l and r, discard this.
 * 
 *          5. use ranges with:
 *      
 *          min(x[i], y[i]) < l < r < max(x[i], y[i])
 * 
 *          and fix maximum and minimum. we can
 *          adchieve this in O(n\log n)
 *
 *  @complexity O(n\log n)
**/  

#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> x(2 * n);
	for (int i = 0; i < 2 * n; ++i) cin >> x[i];
	long long ans = 2e18;
	const int inf = 2e9;
	using ii = pair<int, int>;
	ii p = {inf, -inf}, q = {inf, -inf};
	auto add = [](ii& p, int x) {
		p.first = min(x, p.first);	
		p.second = max(x, p.second);
	};
	for (int i = 0; i < n; ++i) {
		if (x[2 * i] < x[2 * i + 1]) {
			add(p, x[2 * i]);
			add(q, x[2 * i + 1]);
		} else {
			add(p, x[2 * i + 1]);
			add(q, x[2 * i]);
		}
	}
	ans = (p.second - p.first) *1ll* (q.second - q.first);
	int pmx = 0;
	int pmn = 0;
	for (int i = 0; i < n; ++i) {
		if (x[pmx] < x[2*i]) pmx = 2*i;
		if (x[pmx] < x[2*i+1]) pmx = 2*i+1; 
		if (x[pmn] >= x[2*i]) pmn = 2*i;
		if (x[pmn] >= x[2*i+1]) pmn = 2*i+1;
	}
	if (pmx / 2 != pmn / 2) {
		long long temp = x[pmx] - x[pmn];
		ii r = {x[pmn^1], x[pmx^1]};
		if (r.first > r.second) swap(r.first, r.second);
		vector<int> px;
		for (int i = 0; i < n; ++i) {
			if (i == pmn/2 || i == pmx/2) continue;
			if (r.second < min(x[2 * i], x[2 * i + 1])) {
				r.second = min(x[2 * i], x[2 * i + 1]);
			}
			if (r.first > max(x[2 * i], x[2 * i + 1])) {
				r.first = max(x[2 * i], x[2 * i + 1]);
			}
		}
		for (int i = 0; i < n; ++i) {
			if (i == pmn/2 || i == pmx/2) continue;
			if (r.first <= x[2 * i] && x[2 * i] <= r.second) continue; 
			if (r.first <= x[2 * i + 1] && x[2 * i + 1] <= r.second) continue;
			if (x[2 * i] > x[2 * i + 1]) {
				swap(x[2 * i], x[2 * i + 1]);
			}
			px.push_back(i);
		}
		sort(px.begin(), px.end(), [&](int i, int j) {
			return x[2 * i + 1] < x[2 * j + 1];	
		});
		int m = px.size();
		if (m == 0) {
			ans = min(ans, temp*1ll*(r.second - r.first));
		} else {
			vector<int> mnx(m);
			mnx[m-1] = x[2 * px[m-1]];
			for (int i = m-2; i >= 0; --i) {
				mnx[i] = min(mnx[i+1], x[2 * px[i]]);
			}
			ans = min(ans, temp *1ll* (r.second - mnx[0]));
			ans = min(ans, temp *1ll* (x[2 * px[m-1] + 1] - r.first));
			for (int i = 0; i + 1 < m; ++i) {
				ans = min(ans, temp *1ll* (x[2 * px[i] + 1] - mnx[i + 1]));
			}
		}
	}
	cout << ans << '\n';
	return 0;
}