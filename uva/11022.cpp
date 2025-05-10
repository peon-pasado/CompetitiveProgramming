#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
string s;
vi borde(int l, int r) {
	if (r < l) return vi();
	int n = r - l + 1;
	vi b(n+1);
	b[0] = -1;
	//[l, .. r]
	for (int i = 1; i <= n; ++i) {
		b[i] = b[i-1];
		while (b[i] != -1 and s[l+i-1] != s[l+b[i]]) {
			b[i] = b[b[i]];
		}
		b[i] += 1;
	}
	return b;
}
const int maxn = 82;
bool vis[maxn][maxn];
int memo[maxn][maxn];
vi b[maxn][maxn];

int dp(int l, int r) {
	if (r < l) return 0;
	if (l == r) return 1;
	if (vis[l][r]) return memo[l][r];
	int ans;
	int n = r - l + 1;
	int cur = b[l][r][n];
	while (cur >= 0) {
		if (n % (n - cur) == 0) {
			ans = n - cur;
			if (cur != 0) {
				ans = min(ans, dp(l, l + ans - 1));
			}
			break;
		}
		cur = b[l][r][cur];
	}
	for (int k = l; k < r; ++k) {
		ans = min(ans, dp(l, k) + dp(k+1, r));
	}
	vis[l][r] = 1;
	return memo[l][r] = ans;
}

int main() {
	while (cin >> s, s != "*") {
		int n = s.size();
		for (int i = 0; i < n; ++i) {
			for (int j = i; j < n; ++j) {
				b[i][j] = borde(i, j);
			}
		}
		memset(vis, 0, sizeof vis);
		cout << dp(0, n-1) << endl;
	}
	return 0;
}