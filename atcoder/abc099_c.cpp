#include <bits/stdc++.h>
using namespace std;

vector<int> money = {1};
int bt(int p, int n) {
	if (n < 0) return 1e9;
	if (p > n) {
		int ans = 0;
		for (int v : money) {
			ans += n / v;
			n %= v;
		}
		return ans;
	}
	int ans = 1e9;
	for (int j = 0; j < 6; ++j) {
		ans = min(ans, bt(p * 6, n - j * p) + j);
	}
	return ans;
}

int main() {
	
	const int maxN = 100000;
	//for (int i = 6; i <= maxN; i *= 6) money.push_back(i);
	for (int i = 9; i <= maxN; i *= 9) money.push_back(i);
	int n;
	cin >> n;
	sort(money.rbegin(), money.rend());
	cout << bt(6, n) << endl;
	return 0;
}