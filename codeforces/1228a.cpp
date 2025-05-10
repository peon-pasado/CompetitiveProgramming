#include <iostream>
using namespace std;

bool digitos_distintos(int x) {
	int arr[10] = {0};
	while (x > 0) {
		int d = x % 10;
		if (arr[d] == 1) return false;
		arr[d] += 1;
		x /= 10;
	}
	return true;
}

int main() {
	int l, r;
	cin >> l >> r;
	for (int x = l; x <= r; ++x) {
		if (digitos_distintos(x)) {
			cout << x << '\n';
			return 0;
		}
	}
	cout << -1 << '\n';
	return 0;
}