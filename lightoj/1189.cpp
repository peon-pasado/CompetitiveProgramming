#include <iostream>
using namespace std;

int main() {
	long long fact[20];
	fact[0] = 1;
	for (int i = 1; i < 20; ++i) {
		fact[i] = i * fact[i-1];
	}
	int t;
	cin >> t;
	for (int tc=1; tc <= t; ++tc) {
		long long n;
		cin >> n;
		int arr[20];
		int m = 0;
		for (int i = 19; i >= 0; --i) {
			if (n >= fact[i]) {
				n -= fact[i];
				arr[m++] = i;
			}	
		}
		cout << "Case " << tc << ": ";
		if (n == 0) {
			cout << arr[m-1] << "!";
			for (int i = m-2; i >= 0; --i) {
				cout << "+" << arr[i] << "!";
			}
		} else {
			cout << "impossible";
		}
		cout << '\n';
	}
	return 0;
}