#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e6 + 10;
int n, m;
int x[maxN];
long long l[maxN];
long long r[maxN];

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; ++i) {
		scanf("%d", x+i);
	}
	long long c;
	l[0] = 0; c = 1;
	for (int i = 1; i < n; ++i) {
		l[i] = l[i-1] + c * (x[i] - x[i-1]);
		if (i % m == 0) c += 1;
	}	
	r[n-1] = 0; c = 1;
	for (int i = n-2; i >= 0; --i) {
		r[i] = r[i+1] + c * (x[i+1] - x[i]);
		if ((n - i - 1) % m == 0) c += 1;
	}
	long long ans = LLONG_MAX;
	for (int i = 0; i < n; ++i) {	
		ans = min(ans, r[i] + l[i]);
	}
	printf("%lld\n", 2*ans);
	return 0;
}