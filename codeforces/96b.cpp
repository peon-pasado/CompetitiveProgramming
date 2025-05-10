#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<long long> super_suerte_n;
void generar(long long num, int nivel, int balance) {
	if (balance == 0) super_suerte_n.push_back(num);
	if (nivel == 10) return;
	generar(10 * num + 4, nivel + 1, balance+1);
	generar(10 * num + 7, nivel + 1, balance-1);
}

int main() {
	generar(0ll, 0, 0);
	sort(super_suerte_n.begin(), super_suerte_n.end());
	int n;
	cin >> n;
	long long x = 0;
	for (long long s : super_suerte_n) {
		if (s >= n) {
			x = s;
			break;
		}
	}
	cout << x << endl;
	return 0;
}