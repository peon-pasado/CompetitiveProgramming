#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, k;
	cin >> n >> k;
	cout << k * (6 * n - 1) << endl;
	for (int i = 1; i <= n; ++i) {
		for (int v : {5, 4, 3, 1}) {
			cout << k * (6 * i - v) << " ";
		} cout << endl;
	}
	return 0;
}