#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
int val[maxn];
int res[maxn];
int a[maxn];
int n;

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);
		val[x] += 1;		
		a[i] = x;
	}
	for (int i = 1; i <= 1000000; ++i) {
		for (int j = i; j <= 1000000; j += i) {
			res[j] += val[i];
		}
	}
	for (int i = 0; i < n; ++i) {
		printf("%d\n", res[a[i]] - 1);
	}
	return 0;
}