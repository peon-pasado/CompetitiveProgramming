#include <bits/stdc++.h>
using namespace std;

int f(int n) {
	if (n < 10) return n;
	return n%10 + f(n/10);
}

int g(int n) {
	if (f(n) == n) return n;	
	return g(f(n));
}

int main() {
	int n;
	while (cin >> n, n > 0) {
		cout << g(n) << '\n';
	}
	return 0;
}