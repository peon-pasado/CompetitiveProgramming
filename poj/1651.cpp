#include <iostream>
#include <cstdio>
using namespace std;

int n;
const int maxN = 105;
int dp[maxN][maxN];
int d[maxN];

int main () {
	
	while(~scanf("%d", &n)){
		for (int i = 0; i < n; ++i)
			scanf("%d", d+i);

		for (int t = 3; t <= n; ++t)
			for (int i = 0; i + t <= n; ++i){

				int& ans = dp[i][i+t-1] = 1e7;
				
				for (int k = i+1; k < i+t-1; ++k)
					ans = min(ans, dp[i][k] + dp[k][i+t-1] + d[i] * d[k] * d[i+t-1]);
			}
	
		printf ("%d\n", dp[0][n-1]);
	}

	return 0;
}