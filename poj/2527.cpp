#include <iostream>
#include <string.h>
using namespace std;
const int maxN = 1e4 + 10;
int a[maxN];
int n, k;

int main() {
	while (cin >> n >> k, ~n) {
		memset(a, 0, sizeof a);
		for (int i = 0; i <= n; ++i) cin >> a[i];
		if (k == 0) {
			cout << 0 << endl;
			continue;
		}
		while (n >= k) {
			if (a[n] == 0) {
				n -= 1;
				continue;
			}
			int c = a[n];
			a[n] -= c;
			a[n-k] -= c;
		}
		int d = 0;
		for (int i = 0; i < k; ++i) {
			if (a[i] != 0) {
				d = i;
			}
		}
		for (int i = 0; i <= d; ++i) {
			cout << a[i] << " ";
		} cout << endl;
	}
	return 0;
}