#include <bits/stdc++.h>
using namespace std;

int d, s;
long double f(long double x) {
	return x * cosh(d / (2*x)) - x;
}

int main() {
	scanf("%d %d", &d, &s);
	long double lo = 0, hi = 1e12;
	for (int i = 0; i < 600; ++i) {
		long double mid = (hi+lo)/2;
		if (f(mid) >= s) lo = mid;
		else hi = mid;
	}

	printf("%.6Lf\n", 2 * lo * sinh(d / (2*lo)));
	return 0;
}