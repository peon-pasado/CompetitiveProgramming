#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<pair<pair<int, int>, int>> order(3 * n);
		for (int i = 1; i <= 3 * n; ++i) {
			int xi, yi;
			cin >> xi >> yi;
			order[i-1] = {{xi, yi}, i};
		}
		sort(order.begin(), order.end());
		for (int i = 0; i < n; ++i) {
			cout << order[3*i].second << " " 
					 << order[3*i+1].second << " " 
					 << order[3*i+2].second << '\n';
		}
	}
	return 0;
}