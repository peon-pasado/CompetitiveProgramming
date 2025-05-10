#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<pair<int, int>> trees_p, trees_n;
	for (int i = 0; i < n; ++i) {
		int x, a;
		cin >> x >> a;
		if (x > 0) trees_p.push_back({x, a});
		else trees_n.push_back({-x, a});
	}
	sort(trees_p.begin(), trees_p.end());
	sort(trees_n.begin(), trees_n.end());
	if (trees_p.size() < trees_n.size()) {
		swap(trees_n, trees_p);
	}
	int sum = 0;
	for (auto e : trees_n) sum += e.second;
	for (int i = 0; i < trees_p.size() && i < trees_n.size() + 1; ++i) {
		sum += trees_p[i].second;
	}
	cout << sum << '\n';
	return 0;
}