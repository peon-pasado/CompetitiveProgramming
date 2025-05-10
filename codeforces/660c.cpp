#include <iostream>
using namespace std;
const int maxN = 3e5 + 10;
int s[maxN], a[maxN];
int n, k;
int pos;
bool p(int m) {
	for (int i = 0; i + m <= n; ++i) {
		if (s[i + m] - s[i] <= k) {pos = i; return 1;}
	}
	return 0;
}

int main() {
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a+i);
		s[i] = s[i-1] + (a[i] == 0);
	}
	int lo = 0, hi = n;
	while (lo < hi) {
		int mid = lo + (hi - lo + 1) / 2;
		if (p(mid)) lo = mid;
		else hi = mid-1;
	}
	p(lo);
	for (int i = 1; i <= lo; ++i) a[pos+i] = 1;
	printf("%d\n", lo);
	for (int i = 1; i <= n; ++i) printf("%d ", a[i]); puts("");
	return 0;
}