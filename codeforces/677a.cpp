#include <iostream>
using namespace std;

int main() {
	int n, h;
	cin >> n >> h;
	int totalWidth = 0;
	for (int i = 1; i <= n; ++i) {
		int x;
		cin >> x;
		totalWidth += 1 + (x > h);
	}
	cout << totalWidth << endl;
	return 0;
}