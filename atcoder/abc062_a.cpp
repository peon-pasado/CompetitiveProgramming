#include <iostream>
using namespace std;

int grupo(int n) {
	if (n == 1 || n == 3 || n == 5 || n == 7 || n == 8 || n == 10 || n == 12) {
		return 1;
	}
	if (n == 4 || n == 6 || n == 9 || n == 11) {
		return 2;
	}
	if (n == 2) {
		return 3;
	}
	return -1;
}

int main() {
	int x, y;
	cin >> x >> y;
	if (grupo(x) == grupo(y)) cout << "Yes\n";
	else cout << "No\n";
	return 0;
}