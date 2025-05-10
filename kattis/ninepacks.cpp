#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
int n, m;
int h[MAXN], b[MAXN];
int dp[100010][2];

int main() {

	scanf ("%d", &n);
	for (int i = 0; i < n; ++i) 
		scanf("%d", h+i);
	scanf("%d", &m);
	for (int i = 0; i < m; ++i)	
		scanf("%d", b+i);

	int maxi = 1e5;
	
	for (int i = 0; i <= maxi; ++i)	
		dp[i][0] = dp[i][1] = 1000;

	dp[0][0] = 0;
	for (int i = 0; i < n; ++i)
		for(int j = maxi; j >= h[i]; --j)
			dp[j][0] = min(dp[j][0], dp[j - h[i]][0] + 1);

	dp[0][1] = 0;
	for (int i = 0; i < m; ++i)
		for (int j = maxi; j >= b[i]; --j)
			dp[j][1] = min(dp[j][1], dp[j-b[i]][1] + 1);
	
	int ans = INT_MAX;
	for (int i = 1; i <= maxi; ++i)
		if (dp[i][0] != 1000 and dp[i][1] != 1000) ans = min(ans, dp[i][0] + dp[i][1]);

	if (ans != INT_MAX) printf("%d\n", ans);
	else printf("impossible\n");

	return 0;
}