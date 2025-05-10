#include <iostream>
using namespace std;

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		int max_e = 1;
		for (int p = 2; p * p <= n; ++p) {
			if (n % p == 0) {
				int e = 0;
				while (n % p == 0) {
					e += 1;
					n /= p;
				}
				max_e = max(max_e, e);
			}
		}
		cout << max_e << endl;
	}
	return 0;
}