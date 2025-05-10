#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;
long double V[MAXN];
long double d[MAXN][MAXN];
long double dp[1<<16][MAXN];
long double m;
long double x[MAXN], y[MAXN];
long double s[MAXN];
int n;

bool tsp(long double v) {

	V[0] = v;
	for (int i = 1; i < 20; ++i)
		V[i] = V[i-1] * m;

	for (int mask = 1; mask < (1<<n); ++mask) {
		for (int i = 0; i < n; ++i)
			dp[mask][i] = 1e5;

		if (__builtin_popcount(mask) == 1) {
			int i = 31 - __builtin_clz(mask);
			long double temp = hypot(x[i], y[i]) / V[0]; 
			if (temp > s[i]) continue;
			dp[mask][i] = temp;
		}
		else {		
			for (int i = 0; i < n; ++i) {
				if (mask&(1<<i)) {
					int el = __builtin_popcount(mask);
					int mask2 = mask^(1<<i);
					for (int j = 0; j < n; ++j) {
						if(mask2&(1<<j)) {
							if (dp[mask2][j] + d[j][i]/V[el-1] > s[i]) continue;
							dp[mask][i] = min(dp[mask][i], dp[mask2][j] + d[j][i]/V[el-1]);
						}	
					}
				}
			}
		}
	}

	int all = (1<<n)-1;
	for (int i = 0; i < n; ++i) {
		if (dp[all][i] <= s[i]) return 1;
	}
	return 0;
}


int main() {

	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%Lf %Lf %Lf", x+i, y+i, s+i);
	}
	scanf("%Lf", &m);

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			d[i][j] = hypot(x[i] - x[j], y[i] - y[j]);

	long double lo = 0, hi = 1e9;
	for (int i = 0; i < 100; ++i){	
		long double mid = (lo+hi)/2;
		if (tsp(mid)) hi = mid;
		else lo = mid;
	}

	printf("%.8Lf\n", hi);

	return 0;
}