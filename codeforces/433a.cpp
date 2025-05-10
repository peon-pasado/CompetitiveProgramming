#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	int a = 0, b = 0;
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		a += x==100;
		b += x==200;
	}
	if (a%2 == 1) cout << "NO\n";
	else if (b%2 == 0) cout << "YES\n";
	else if (a > 1) cout << "YES\n";
	else cout << "NO\n";
	return 0;
}