#include <bits/stdc++.h>
using namespace std;

const int mod = 10007;
int add (int a, int b) {
	return (a+b)%mod;
}

string s;
int n;
const int maxN = 1005;
int dp[maxN][maxN];

int main () {
	
	cin >> n;
	for (int tc = 1; tc <= n; ++tc) {

		cin >> s;
		for (int i = 0; i < s.size(); ++i)
			dp[i][i] = 1;

		for (int t = 2; t <= s.size(); ++t)
			for (int i = 0; i + t <= s.size(); ++i){

				int& ans = dp[i][i+t-1] = add(dp[i+1][i+t-1], dp[i][i+t-2]);			

				if (s[i] == s[i+t-1]) ans = add(ans, 1);
				else if (t != 2) ans = add(ans, mod - dp[i+1][i+t-2]);
			}
	
		printf ("Case %d: %d\n", tc, dp[0][(int)s.size()-1]);
	}

	return 0;
}