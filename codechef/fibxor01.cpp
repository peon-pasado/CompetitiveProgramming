#include <iostream>
using namespace std;

int a, b, n;
int f(int n) {
	if (n == 0) return a;
	if (n == 1) return b;
	return f(n-1) ^ f(n-2);
}


int main() {
	int t;
	cin >> t;
	while (t--) {
		cin >> a >> b >> n;
		cout << f(n % 3) << endl;
	}
	return 0;
}