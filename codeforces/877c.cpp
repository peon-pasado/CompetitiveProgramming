#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	cout << n + n/2 << endl;
	for (int i = 1; i <= n/2; ++i) {
		cout << 2 * i << " ";
	}
	for (int i = 1; i <= (n+1)/2; ++i) {
		cout << 2 * i - 1 << " ";
	}
	for (int i = 1; i <= n/2; ++i) {
		cout << 2 * i << " ";
	}
	cout << endl;
	return 0;
}