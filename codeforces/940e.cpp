#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e5 + 10;
int n, c;
int a[maxN];
long long sum[maxN];
long long f[maxN];
int mi[maxN];

int main() {
	cin >> n >> c;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		sum[i] = sum[i-1] + a[i];
	}
	if (c == 0) return puts("0"), 0;
	deque<int> s;
	for (int i = 1; i <= n; ++i) {
		while (not s.empty() and a[s.back()] >= a[i]) s.pop_back();
		while (not s.empty() and i - s.front() + 1 > c) s.pop_front();
		s.push_back(i);
		mi[i] = s[0];
	}
	for (int i = 1; i <= n; ++i) {
		f[i] = 4e18;
	}
	f[0] = 0;
	for (int i = 1; i <= n; ++i) {
		if (i >= c) f[i] = min(f[i], f[i-c] + sum[i] - sum[i-c] - a[mi[i]]);
		f[i] = min(f[i], f[i-1] + a[i]);
	}
	cout << f[n] << endl;
	return 0;
}