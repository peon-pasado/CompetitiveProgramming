#include <iostream>
#include <vector>
using namespace std;

const int mod = 1e9 + 7;
const int maxn = 370;
using ll = long long;
int f[maxn], f_inv[maxn], r[maxn];
int memo[maxn][maxn], memo_acc[maxn][maxn];
bool vis[maxn][maxn], vis_acc[maxn][maxn];

int add(int a, int b) {
	return (a+b)%mod;
}

int mul(ll a, ll b) {
	return a*b%mod;
}

int binom(int n, int k) {
	if (n < k) return 0;
	return mul(f[n], mul(f_inv[k], f_inv[n-k]));
}

int dp(int, int);

int dp_acc(int n, int d) {
	if (vis_acc[n][d]) return memo_acc[n][d];
	vis_acc[n][d] = 1;
	int& acc = memo_acc[n][d] = 0;
	for (int i = 0; i <= d; ++i) {
		acc = add(acc, dp(n, i));
	}
	return acc;
}

int dp(int n, int d) {
	if (n < 0 || d < 0) return 0;
	if (n <= 1) return n==d;
	if (vis[n][d]) return memo[n][d];
	vis[n][d] = 1;
	int& ans = memo[n][d] = 0;
	
	for (int i = 1; i < n-1; ++i) {
		int temp = mul(n, dp_acc(n-i-1, d-2));
		temp = mul(temp, mul(binom(n-2, i-1), dp(i, d-1)));
		ans = add(ans, temp);
	}
	
	for (int i = 1; i < n-1; ++i) {
		int temp = mul(n, dp(n-i-1, d-1));
		temp = mul(temp, mul(binom(n-2, i-1), dp_acc(i, d-2)));
		ans = add(ans, temp);
	}
	
	for (int i = 1; i < n-1; ++i) {
		int temp = mul(n, dp(n-i-1, d-1));
		temp = mul(temp, mul(binom(n-2, i-1), dp(i, d-1)));
		ans = add(ans, temp);
	}
	ans = add(ans, mul(2 * n, dp(n-1, d-1)));
	return ans;
}

int main() {
	f[0] = f_inv[0] = r[1] = 1;
	for (int i = 1; i < maxn; ++i) {
		if (i > 1) r[i] = mul(r[mod%i], mod - mod/i);
		f[i] = mul(i, f[i-1]);
		f_inv[i] = mul(r[i], f_inv[i-1]);
	}
	int t;
	cin >> t;
	for (int tc=1; tc<=t; ++tc) {
		int n, d;
		cin >> n >> d;
		cout << "Case #" << tc << ": " << dp(n, d) << '\n';
	}
	return 0;
}