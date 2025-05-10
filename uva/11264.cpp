#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 10;
int c[maxn];
int t, n;

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%d", c+i);
		}
		int res = 1;
		int mx = 0;
		for (int i = 0; i + 1 < n; ++i) {
			if (mx + c[i] < c[i+1]) {
				mx += c[i];
				res += 1;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}