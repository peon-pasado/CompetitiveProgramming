#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
	return b==0 ? a : gcd(b, a%b);
}

int main() {
	int a, b;
	while (cin >> a >> b) {
		int g = gcd(a, b);
		cout << g << " " << a/g*b << '\n'; 
	}
	return 0;
}