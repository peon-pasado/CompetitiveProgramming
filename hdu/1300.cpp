#include <bits/stdc++.h>
using namespace std;

const int N = 105;
int dp[N];
int sum[N], a[N], p[N];
int t, n;


int main () {	
	scanf ("%d", &t);	

	while (t --) {

		scanf ("%d", &n);

		for (int i = 1; i <= n; ++i) {
			scanf ("%d %d", a+i, p+i);
		}

		for (int i = 1; i <= n; ++i) {
			sum[i] = a[i] + sum[i - 1];
		}
		
		for (int i = 1; i <= n; ++i) {
			dp[i] = 2e9;

			for (int j = 0; j < i; ++j) {						
				dp[i] = min (dp[i], dp[j] + (sum[i] - sum[j] + 10) * p[i]);
			}
		}
	
		printf ("%d\n", dp[n]);
	}


	return 0;
}