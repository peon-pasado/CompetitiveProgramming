#include <bits/stdc++.h>
using namespace std;
const int maxN = 3e5 + 10; 
int n, m;
int diff[maxN];
int x[maxN], y[maxN];
long long acc[maxN];
long long ans[maxN];

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; ++i) {
		scanf("%d %d", x+i, y+i);
	}
	for (int i = 0; i < n; ++i) {
		diff[i] = x[i] - y[i];
	}
	long long sumY = 0;
	for (int i = 0; i < n; ++i) {
		sumY += y[i];
	}
	sort(diff, diff+n);
	acc[0] = diff[0];
	for (int i = 1; i < n; ++i) {
		acc[i] = acc[i-1] + diff[i];
	}
	for (int i = 0; i < n; ++i) {
		int lo = 0, hi = n-1;
		while (lo < hi) {
			int mid = lo + (hi - lo + 1) / 2;
			if (diff[mid] <= x[i] - y[i]) lo = mid;
			else hi = mid - 1;
		}
		ans[i] = n * 1ll * x[i] + sumY;
		if (diff[lo] <= x[i] - y[i]) {
			ans[i] -= (lo + 1) * 1ll * (x[i] - y[i]);
			ans[i] += acc[lo];
		}
		ans[i] -= x[i] + y[i];		
	}
	for (int i = 0; i < m; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;
		ans[a] -= min(x[a] + y[b], x[b] + y[a]);
		ans[b] -= min(x[a] + y[b], x[b] + y[a]);	
	}
	for (int i = 0; i < n; ++i) {
		printf("%lld ", ans[i]);
	} puts("");
	return 0;
}