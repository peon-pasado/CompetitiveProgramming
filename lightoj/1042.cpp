#include <iostream>
#include <bitset>
using namespace std;

int main() {
	int t;
	cin >> t;
	for (int tc=1; tc <= t; ++tc) {
		int n;
		cin >> n;
		int k = __builtin_ctz(n);
		n ^= (1<<k)-1;
		int l = __builtin_ctz(~n);
		n ^= (1<<k+2)-1<<l-k-1;
		cout << "Case " << tc << ": " << n << endl;
	}
	return 0;
}