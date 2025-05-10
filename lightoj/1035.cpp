#include <bits/stdc++.h>
using namespace std;

int main() {
	vector<int> prime;
	for (int i = 2; i <= 100; ++i) {
		int m = i;
		bool fun = 1;
		for (int j = 2; j * j <= m; ++j) {
			if (m % j == 0) fun = 0; 
		}
		if (fun) prime.push_back(i);
	}
	
	int t;
	cin >> t;
	for (int tc = 1; tc <= t; ++tc) {
		int n;
		cin >> n;
		cout << "Case " <<  tc << ": " << n << " =";
		bool fst = 1;
		for (int p : prime) {
			int m = n / p;
			int ans = 0;
			while (m > 0) {
				ans += m;
				m /= p;
			}
			if (ans > 0) {
				cout << (fst ? " " : " * ") << p << " (" << ans << ")";
				fst = 0;
			}
		}
		cout << endl;
	}
	return 0;
}