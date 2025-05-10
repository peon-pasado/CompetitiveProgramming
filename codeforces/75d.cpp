#include <bits/stdc++.h>
using namespace std;
const int maxN = 55;
const int maxM = 2.5e5 + 10;
vector<int> v[maxN];
int n, m;
int sum[maxN];
int suff[maxN];
int pref[maxN];
int sol[maxN];
int a[maxM];

long long go(int l, int r) {
	if (r < l) return LLONG_MIN;
	if (l == r) {
		return sol[a[r]];
	}
	int mid = (l+r)/2;
	long long L = 0, sL = 0;	
	long long R = 0, sR = 0;
	for (int i = mid+1; i <= r; ++i) {
		sR += pref[a[i]];
		R = max(R, sR);
		sR -= pref[a[i]] - sum[a[i]];
	}
	for (int i = mid-1; i >= l; --i) {
		sL += suff[a[i]];
		L = max(L, sL);
		sL -= suff[a[i]] - sum[a[i]];
	}
	long long ans = sum[a[mid]] + L + R;
	ans = max(ans, (long long)sol[a[mid]]);
	ans = max(ans, pref[a[mid]] + L);
	ans = max(ans, suff[a[mid]] + R);
	ans = max(ans, go(l, mid-1));	
	ans = max(ans, go(mid+1, r));
	return ans;
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		int l;
		scanf("%d", &l);
		for (int j = 1; j <= l; ++j) {
			int x;
			scanf("%d", &x);
			v[i].emplace_back(x);
			sum[i] += x;
		}
		sol[i] = pref[i] = v[i][0];			
		suff[i] = v[i][l-1];
		int a = 0, b = 0, c = 0;
		for (int j = 0; j < l; ++j) {
			a += v[i][j];
			b += v[i][l-j-1];			
			pref[i] = max(pref[i], a);
			suff[i] = max(suff[i], b);
			c = v[i][j] + max(0, c);
			sol[i] = max(sol[i], c);
		}
	}
	for (int i = 1; i <= m; ++i) {
		scanf("%d", a+i);
	}
	printf("%lld\n", go(1, m));
	return 0;
}