#include <bits/stdc++.h>
using namespace std;

const int maxn = 5010;
int a[maxn], b[maxn];
int k, q, d, m;
long long n;
vector<int> arr;
bool vis[80][2 * maxn][2];
bool memo[80][2 * maxn][2];
int tr[80][2 * maxn][2];

void setup() {
	arr.clear();
	if (n == 0) arr.push_back(0);
	while (n > 0) {
		arr.push_back(n % k);
		n /= k;
	}
	memset(vis, 0, sizeof vis);
}

using pii = pair<int, int>;
pii get(int a) {
	if (a >= 0) return {a%k, a/k};
	int t = (-a + k - 1) / k;
	return {a + t * k, -t};
}

bool dp(int a[], int pos, int carry, bool fi) {
	if (pos >= arr.size() && carry == 0) return 1;
	if (pos >= arr.size() + 20) return 0;
	if (vis[pos][maxn + carry][fi]) return memo[pos][maxn + carry][fi];
	bool& ans = memo[pos][maxn + carry][fi] = 0;
	tr[pos][maxn + carry][fi] = d;
	int cur = pos < arr.size() ? arr[pos] : 0;
	if (pos > 0) {
		auto q = get(carry);
		if (q.first == cur && dp(a, pos+1, q.second, 1)) {
			ans = 1;	
		}
	} 
	if (!fi && !ans) {
		for (int i = 0; i < d; ++i) {
				auto q = get(a[i] + carry);
				if (q.first == cur && dp(a, pos+1, q.second, 0)) {
					tr[pos][maxn + carry][fi] = i;
					ans = 1;
					break;
				}
		}
	}
	vis[pos][maxn + carry][fi] = 1;
	return ans;
}

int main() {
	cin >> k >> q >> d >> m;
	for (int i = 0; i < d; ++i) {
		cin >> a[i];
		b[i] = -a[i];
	}
	while (q--) {
		cin >> n;
		int sign = n >= 0 ? 1 : -1;
		if (n < 0) n = -n;
		setup();
		bool ans = 0;
		if (sign == 1) ans = dp(a, 0, 0, 0);
		else ans = dp(b, 0, 0, 0);
		if (ans) {
			vector<int> res;
			for (int i = 0, carry = 0, fi = 0; ; ++i) {
					if (i >= arr.size() && carry == 0) break;
					int idx = tr[i][maxn + carry][fi];
					if (idx == d) break;
					res.push_back(a[idx]);
					carry = get(carry + sign * a[idx]).second;
			}
			reverse(res.begin(), res.end());
			for (int i = 0; i < res.size(); ++i) {
				cout << res[i] << " \n"[i+1==res.size()];
			}
		} else {
			cout << "IMPOSSIBLE\n";
		}
	}
	return 0;
}