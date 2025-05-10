#include <iostream>
using namespace std;

int main() {
	int n;
	while (cin >> n, n) {
		cout << n << " ";
		int sum = 0;
		int k = 1, coin = 1;
		for (int i = 1; i <= n; ++i) {
			sum += coin;
			if (i == k) {
				coin += 1;
				k += coin;
			}
		}
		cout << sum << endl;
	}
	return 0;
}