#include <iostream>
using namespace std;

const int maxn = 1<<20;
int a[maxn];
int f[maxn<<1][2];

void update(int m, int p) {
	if (f[m][0] < p) {
		f[m][1] = f[m][0];
		f[m][0] = p;
	} else {
		f[m][1] = max(f[m][1], p);
	}
}

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		update(a[i], i);
	}
	for (int i = 0; i < 21; ++i) {
		for (int j = 0; j < 1<<21; ++j) {
			if (~j & (1<<i)) {
				update(j, f[j^(1<<i)][0]);
				update(j, f[j^(1<<i)][1]);
			}
		}
	}
	int u = (1<<21)-1;
	int ans = 0;
	for (int i = 1; i <= n-2; ++i) {
		int v = u ^ a[i];
		int best = 0;
		for (int j = 20; j >= 0; --j) {
			if (v & (1<<j)) {
				if (f[best ^ (1<<j)][1] > i) {
					best ^= 1<<j;
				}
			}	
		}
		ans = max(ans, a[i] | best);
	}
	cout << ans << '\n';
	return 0;
}