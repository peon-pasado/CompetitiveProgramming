#include <bits/stdc++.h>
using namespace std;

map<vector<int>, int> g;
int gn(vector<int> x) {
	if (g.count(x)) return g[x];
	if (x.size() == 1) return x[0];
	set<int> ss;
	for (int i = 1; i <= x.back(); ++i) {
		vector<int> v;
		for (int e : x) { 
			if (e == i) continue;
			v.push_back(e);
			if (e > i) v.back() -= i;
		}
		sort(begin(v), end(v));
		v.resize(unique(begin(v), end(v)) - begin(v));
		ss.insert(gn(v));
	}
	int cnt = 0;
	while (ss.count(cnt)) cnt += 1;
	return g[x] = cnt;
}

int main() {
	int n;
	cin >> n;
	map<int, vector<int>> pot;
	for (int i = 1; i <= n; ++i) {
		int x;
		cin >> x;
		for (int i = 2; i*i <= x; ++i) {
			if (x % i == 0) {
				int e = 0;
				while (x % i == 0) {
					e += 1;
					x /= i;
				}
				pot[i];
				pot[i].push_back(e);
			}
		}
		if (x > 1) {
			pot[x];
			pot[x].push_back(1);
		} 
	}
	int r = 0;
	for (auto& e : pot) {
		sort(begin(e.second), end(e.second));
		e.second.resize(unique(begin(e.second), end(e.second)) - begin(e.second));
		r ^= gn(e.second);
	}
	if (r == 0) cout << "Arpa" << endl;
	else cout << "Mojtaba" << endl;
	return 0;
}