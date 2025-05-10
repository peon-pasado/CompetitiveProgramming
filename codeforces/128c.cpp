#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;

int add(int a, int b) {return (a+b)%mod;}
int mul(long long a, long long b) {return a*b%mod;}

const int maxN = 1010;
int memo[maxN][maxN];
bool vis[maxN][maxN];
int dp(int n, int k) {
	if (k == 0) return 1;
	if (vis[n][k]) return memo[n][k];
	vis[n][k] = 1;
	int ans = 0;
	for (int i = 1; i < n-1; ++i) {
		ans = add(ans, mul(n-1-i, dp(i, k-1)));
	}
	return memo[n][k] = ans;
}

int main() {
	int n, m, k;
	cin >> n >> m >> k;
	cout << mul(dp(n, k), dp(m, k)) << endl; 
	
	return 0;
}