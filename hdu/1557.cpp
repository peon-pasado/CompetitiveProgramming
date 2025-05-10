#include <iostream>
using namespace std;
const int maxN = 20;
long long sum[1<<maxN];
int t, n;
int a[maxN];
int ans[maxN];

int main() {
	int t;
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 0; i < n; ++i) {
			cin >> a[i];
		}
		for (int mask = 1; mask < (1<<n); ++mask) {
			int lso = mask & -mask;
			sum[mask] = sum[mask ^ lso] + a[31 - __builtin_clz(lso)];
		}
		for (int i = 0; i < n; ++i) {
			ans[i] = 0;
		}
		for (int mask = 1; mask < (1<<n); ++mask) {
			int cmask = mask ^ ((1<<n)-1);
			if (sum[mask] > sum[cmask]) {
				for (int i = 0; i < n; ++i) {
					if (mask & (1<<i)) {
						if (sum[mask] - 2*a[i] <= sum[cmask]) {
							ans[i] += 1;
						} 
					}
				}
			}
		}
		for (int i = 0; i < n; ++i) {
			cout << ans[i] << " \n"[i+1==n];
		}
	}
	return 0;
}