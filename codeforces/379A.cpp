#include <iostream>
using namespace std;

int main() {
	int a, b;
	cin >> a >> b;
	int velas = a, velas_malogradas = 0;
	int res = 0;
	while (velas > 0) {
		res += velas;
		velas_malogradas += velas;
		velas = velas_malogradas / b;
		velas_malogradas %= b;
	}
	cout << res << '\n';
	return 0;
}