#include <bits/stdc++.h>
using namespace std;
const int maxN = 3e5 + 10;
bool vis[maxN][101];
int memo[maxN][101];
int n;
int a[maxN];

int dp(int pos, int sum) {
	if (sum > 100) return 1e9;
	if (pos == n) return 0;
	if (vis[pos][sum]) return memo[pos][sum];
	int ans = 1e9;
	ans = min(ans, dp(pos+1, sum + a[pos]/10) + a[pos]);
	int p = min(sum, a[pos]);
	ans = min(ans, dp(pos+1, sum - p) + a[pos] - p);
	vis[pos][sum] = 1;
	return memo[pos][sum] = ans;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", a+i);
		a[i] /= 100;
	}
	printf("%d\n", dp(0, 0) * 100);
	return 0;
}