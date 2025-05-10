#include <bits/stdc++.h>
using namespace std;

const int N = 1002;
int t, n;
int dp[N][N], T[N][N]; 


int main(){

	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j){
				scanf("%d", &T[i][j]);
				dp[i][j] = T[i][j] + dp[i][j-1] + dp[i-1][j] - dp[i-1][j-1];
			}

		int m = dp[n][n];
		vector<int> d;
		for(int i = 1; i*i <= m; ++i)
			if(m%i == 0){
				d.push_back(i);
				d.push_back(m/i);
			}

		if(d.empty()){
			puts("0");
			continue;
		}

		int ans = INT_MAX;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				for(int k = 0; k < d.size(); ++k){
					int l = d[k];
					int r = m/d[k];
					if(i + l - 1 > n or j + r - 1 > n) continue;
					
					ans = min(ans, m - dp[i+l-1][j+r-1] + dp[i+l-1][j-1] + dp[i-1][j+r-1] - dp[i-1][j-1]);
				}

		if(ans == INT_MAX) puts("-1");
		else printf("%d\n", ans);
	}

	return 0;
}