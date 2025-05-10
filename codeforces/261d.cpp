#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e5 + 10;
bool vis[maxN];
int k, n, m, t;
int LIS[maxN];
int Min[maxN];
int a[maxN];

int main() {
	scanf("%d %d %d %d", &k, &n, &m, &t);
	while (k--) {
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d", a+i);
			if (not vis[a[i]]) {
				cnt += 1;
			}
			vis[a[i]] = 1;
			LIS[a[i]] = 0;
		}
		for (int i = 0; i <= m; ++i) {
			Min[i] = 1e9;
		}
		Min[0] = 0;
		for (int i = 0; i < t and i < cnt; ++i) {
			for (int j = 0; j < n; ++j) {
				while (Min[LIS[a[j]]] < a[j]) {
					LIS[a[j]] += 1;
				}
				Min[LIS[a[j]]] = a[j];
			}
		}
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			ans = max(ans, LIS[a[i]]);
			vis[a[i]] = 0;
		}
		printf("%d\n", ans);
	}
	return 0;
}