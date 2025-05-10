#include <iostream>
using namespace std;

int main() {
	int a, b;
	cin >> a >> b;
	int t = 0;
	do {
		a *= 3;
		b *= 2;
		t += 1;
	} while (a <= b);
	cout << t << endl;
	return 0;
}