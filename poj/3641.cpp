#include <iostream>
using namespace std;

int pow_mod(int a, int b, int m) {
	int r = 1;
	while (b > 0) {
		if (b&1) r = r*1ll*a%m;
		a = a*1ll*a%m;
		b >>= 1;
	}
	return r;
}

bool is_prime(int n) {
	for (int i = 2; i*i <= n; ++i)	
		if (n % i == 0) return 0;
	return 1;
}

int main() {
	int p, a;
	while (cin >> p >> a, p+a) {
		if (pow_mod(a, p, p) == a && !is_prime(p)) {
			cout << "yes\n";
		} else {
			cout << "no\n";
		}
	} 
	return 0;
}