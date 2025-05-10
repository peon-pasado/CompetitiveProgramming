#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	while (cin >> n) {
		pair<int, int> a = {-2e9, 0};
		for (int i = 0; i < n; ++i) {
			int x;
			cin >> x;
			if (x == a.first) a.second++;
			else if (a.second < 1) a = {x, 1};
			else a.second--;
		}
		cout << a.first << '\n';
	}
	return 0;
}