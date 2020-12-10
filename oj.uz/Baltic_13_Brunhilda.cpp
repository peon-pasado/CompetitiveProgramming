/**
 * @author Miguel Mini
 * @tag dp, greedy, math
 * @idea
 *      - Greedy observation: f(n) <= f(n+1) for all n \in N.
 *
 *      - We need to find the smallest p * (n // p) for every p \in primes.
 *
 *      - g(n) = n - k(n), g(n): smallest p * (n // p). with 
 *      k(n) = max(k(n + t) - t, t >= 0) -> k(n) = max(k(n), k(n+1) - 1). 
 *
 *      - dp(n) = dp(g(n)) if n != g(n) or dp(n) = oo.
 *
**/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e7 + 10;
int dp[maxn];
int link[maxn];

int main() {
	int m, q;
	scanf("%d%d", &m, &q);
	for (int i=0; i<m; ++i) {
		int x;
		scanf("%d", &x);
		for (int j=x-1; j<maxn; j+=x) {
			link[j] = x-1;
		}
	}
	for (int i = maxn-2; i >= 1; --i) {
		if (link[i] < link[i+1] - 1) {
			link[i] = link[i+1] - 1;
		}
	}
	const int inf = 1e9;
	for (int i = 1; i < maxn; ++i) {
			if (link[i] == 0) dp[i] = inf;
			else dp[i] = min(inf, dp[i - link[i]] + 1);
	}
	while (q--) {
		int n;
		scanf("%d", &n);
		if (dp[n] > n) puts("oo\n");
		else printf("%d\n", dp[n]);
	}
	return 0;
}
