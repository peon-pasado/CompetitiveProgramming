#include <bits/stdc++.h>
using namespace std;
int n, m;
map<int, int> cnt[2][32];

int main() {
	scanf("%d %*d", &n);
	for (int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);	
		for (int k = 1; k <= 31; ++k) {
			cnt[0][k][x & ((1ll<<k)-1)] += 1; 
		}
	}
	scanf("%d %*d", &m);
	for (int i = 0; i < m; ++i) {
		int x;
		scanf("%d", &x);
		for (int k = 1; k <= 31; ++k) {
			cnt[1][k][x & ((1ll<<k)-1)] += 1;
		}
	}
	int ans = 2;
	for (int t = 0; t < 2; ++t) {
		for (int k = 1; k <= 31; ++k) {
			for (auto e : cnt[t][k]) {
				ans = max(ans, e.second + cnt[t^1][k][(e.first + (1ll<<k-1))&((1ll<<k)-1)]);
			}
		}
	}
	printf("%d\n", ans);
	return 0;	
}