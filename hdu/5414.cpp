#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	for (int i = 0; i < T; ++i) {
		string s, t;
		cin >> s >> t;
		vector<pair<char, int>> fs, ft;
		for (int i = 0; i < s.size(); ++i) {
			if (fs.empty() || fs.back().first != s[i]) {
				fs.push_back({s[i], 1});
			} else {
				fs.back().second += 1;
			}
		}
		for (int i = 0; i < t.size(); ++i) {
			if (ft.empty() || ft.back().first != t[i]) {
				ft.push_back({t[i], 1});
			} else {
				ft.back().second += 1;
			}
		}
		if (fs[0].first == ft[0].first && fs[0].second >= ft[0].second) {
			int j = 0;
			for (int i = 0; i < ft.size(); ++i) {
				if (j < fs.size() && fs[j].first == ft[i].first) {
					if (fs[j].second <= ft[i].second) j += 1;
					else {
						fs[j].second -= ft[i].second;
					}
				}
			}
			if (j == fs.size()) cout << "Yes" << '\n';
			else cout << "No" << '\n';
		} else {
			cout << "No" << '\n';
		}
	}
	return 0;
}