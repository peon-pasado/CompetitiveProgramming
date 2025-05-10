#include <iostream>
using namespace std;

int main() {
	int t;
	cin >> t;
	for (int i = 1; i <= t; ++i) {
		long long n;
		cin >> n;
		long long m = 1;
		while (n%2 == 0) {
			n /= 2;
			m *= 2;
		}
		if (m%2 == 0) cout << "Case " << i << ": " << n << " " << m << endl;
		else cout << "Case " << i << ": " << "Impossible" << endl;
	}
	return 0;
}