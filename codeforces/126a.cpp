#include <bits/stdc++.h>
using namespace std;

int main() {
	long long t1, t2, x1, x2, t0;
	cin >> t1 >> t2 >> x1 >> x2 >> t0;
	
	vector<pair<int, int>> candidates;
	for (long long sum = 1; sum <= x1+x2; ++sum) {
	    long long l = max(0ll, sum-x2);
	    long long r = min(sum, x1);
	    if (t1 < t2) r = min(r, sum * (t2 - t0) / (t2 - t1));
	    if (l <= r) {
	        candidates.push_back({r, sum - r});
	    }
	}
	
	/**
	pair<int, int> q = candidates[0];
	for (int i = 1; i < candidates.size(); ++i) {
		pair<int, int> p = candidates[i];
		auto l = (p.first*1ll*t1 + p.second*1ll*t2) * (q.first + q.second);
	    auto r = (q.first*1ll*t1 + q.second*1ll*t2) * (p.first + p.second);
	    if (l < r || (l == r && p.first + p.second > q.first + q.second)) {
	    	q = p;	
	    }
	}
	auto best = q;
	**/
	auto best = *min_element(candidates.begin(), candidates.end(), 
	  [&](pair<int, int> p, pair<int, int> q) {
	      auto l = (p.first*1ll*t1 + p.second*1ll*t2) * (q.first + q.second);
	      auto r = (q.first*1ll*t1 + q.second*1ll*t2) * (p.first + p.second);
	      return l < r || (l == r && p.first + p.second > q.first + q.second); 
	  }
	);
	cout << best.first << " " << best.second << '\n';
	return 0;
}