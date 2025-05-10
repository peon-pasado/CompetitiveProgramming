#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 10;
int nxt[maxn];
int a[maxn];
int b[maxn];
int cnt[maxn];

long long calc(int l, int r, int p, int v) {
	int lo = l, hi = r;
	while (lo < hi) {
		int mid = (lo + hi) / 2;
		if (mid - p + 1 < v) lo = mid + 1;
		else hi = mid;
	}
	if (lo - p + 1 < v) return 0;
	int f = lo;
	//[lo, lo + 1, ..., r]
	lo = p; hi = l;
	while (lo < hi) {
		int mid = (lo + hi + 1) / 2;
		if (f - mid + 1 >= v) lo = mid;
		else hi = mid-1;
	}
	int m = r - f + 1;
	//min(l, lo+i)
	//i < l - lo
	
	//[p, lo], [p, lo+1], [p, lo+2], ..., [p, min(l, lo+m-1)]
	//for (int i = 0; i < min(m, l - lo); ++i) ans += (lo + i) - p + 1;
	//for (int i = min(m, l - lo); i < m; ++i) ans += l - p + 1;
	
	int cc = min(m, l - lo);
	long long ans = 0;
	ans += (l - p + 1) *1ll* max(0, m - cc);
	ans += (lo - p + 1) *1ll* max(0, cc);
	ans += cc *1ll* (cc - 1) / 2;
	return ans;
}

int main() {
	int t, n, K;
	cin >> t;
	while (t--) {
		cin >> n >> K;
		for (int i = 0; i < n; ++i) {
			cin >> a[i]; 
			b[i] = max(a[i] - K, 1);
		}
		a[n] = n + 1;
		stack<int> s;
		s.push(n);
		for (int i = n-1; i >= 0; --i) {
			while (!s.empty() && a[s.top()] <= a[i]) s.pop();
			nxt[i] = s.top();
			s.push(i);
		}
		for (int i = 0; i <= n; ++i) cnt[i] = 0;
		long long ans = 0;
		int last = 0;
		for (int l = 0, r = 0; l < n; ++l) {
			last = max(last, l);
			while (r < n && cnt[a[r]] == 0) {
				cnt[a[r]] += 1;
				if (r == nxt[last]) last = r;
				if (r - l + 1 >= b[last]) {
					//[l, l']
					int lo = l, hi = last; 
					while (lo < hi) {
						int mid = (lo + hi + 1) / 2;
						if (r - mid + 1 >= b[last]) lo = mid;
						else hi = mid-1;
					}
					//cout << l << " " << r << " " << last << " " <<  lo - l + 1 << endl;
					ans += (lo - l + 1);
				}
				r += 1;
			}
			int f = l + 1;
			if (last == l) last = l + 1;
			while (f < r && f != nxt[l]) {
				if (f == nxt[last]) last = f;
				//if (a[f] > a[last]) last = f;
				//cout << ans << " ";
				ans += calc(f, min(r, nxt[f]) - 1, l + 1, b[f]);
				//cout << ans << endl;
				f = nxt[f];
			}
			cnt[a[l]] -= 1;
		}
		cout << ans << endl;
	}
	return 0;
}