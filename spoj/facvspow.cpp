#include <bits/stdc++.h>
using namespace std;
const int maxn = 2.8e6 + 1;
double f[maxn];

int main() {
	f[1] = 0;
	for (int i = 2; i < maxn; ++i) {
		f[i] = f[i-1] + log(i);
	}
	int t;
	cin >> t;
	while (t--) {
		int a;
		cin >> a;
		int lo = 1, hi = maxn-1;
		double la = log(a);
		while (lo < hi) {
			int mid = lo + (hi-lo)/2;
			if (f[mid] <= mid * la) lo = mid+1;
			else hi = mid;
		}
		cout << lo << endl;
	}
	return 0;
}