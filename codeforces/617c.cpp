#include <bits/stdc++.h>
using namespace std;

long long distance(pair<int, int> p, pair<int, int > q) {
	return (long long) (p.first - q.first) * (p.first - q.first) +
				 (long long) (p.second - q.second) * (p.second - q.second); 
}

int main() {
	int n;
	cin >> n;
	vector<pair<int, int>> p(n + 2);
	for (int i = 0; i < n+2; ++i) {
		int x, y;
		cin >> x >> y;
		p[i] = {x, y};
	}
	long long res = 1e18;
	for (int i = 0; i < n; ++i) {
		long long r1 = distance(p[0], p[i + 2]);  
		long long r2 = 0;
		for (int j = 0; j < n; ++j) {
			if (distance(p[0], p[j+2]) > r1) {
				r2 = max(r2, distance(p[1], p[j+2]));
			}
		}
		res = min(res, r1 + r2);
	}
	long long r3 = 0;
	for (int i = 0; i < n; ++i) {
		r3 = max(r3, distance(p[1], p[i+2]));
	}
	res = min(res, r3);
	cout << res << '\n';
	return 0;
}