#include <bits/stdc++.h>
using namespace std;

int main() {
	string t;
	cin >> t;
	deque<char> dt; //dt = t
	for (auto c : t) {
		dt.push_back(c);
	}
	string s = "";
	while (!dt.empty()) {
		if (dt.size() % 2 == 0) {
			s += dt.back();
			dt.pop_back();
		} else {
			s += dt.front();
			dt.pop_front();
		}
	}
	reverse(s.begin(), s.end());
	cout << s << '\n';
	return 0;
}