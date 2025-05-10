#include <bits/stdc++.h>
using namespace std;
const int maxN = 2e5 + 10;
long long f[maxN];

int main() {
	int n, k, x;
	cin >> n >> k >> x;	
	const int inf = 1e9 + 10;
	int l = 0;
	int mi = 1e9, ma = -1e9;
	for (int i = 1; i <= n; ++i) {
		cin >> f[i];
		if (f[i] < 0) l += 1;
		mi = min(1ll*mi, abs(f[i]));	
	}	
	if (l%2 == 0) {
		for (int i = 1; i <= n; ++i) {
			if (abs(f[i]) == mi) {
				int d = min(abs(f[i]) / x + 1, 1ll*k);
				k -= d;
				if (f[i] < 0) f[i] += x *1ll* d;
				else f[i] -= x *1ll* d;
				break;
			}
		}
	}	
	set<pair<long long, int>> s;
	for (int i = 1; i <= n; ++i) {
		s.insert({abs(f[i]), i});
	}
	while (k > 0) {
		auto q = *(s.begin());	
		s.erase(s.begin());
		if (f[q.second] >= 0) f[q.second] += x;
		else f[q.second] -= x;
		q.first += x;	
		s.insert(q);
		k -= 1;
	}
	for (int i = 1; i <= n; ++i) {
		cout << f[i] << " ";
	} cout << endl;
	return 0;
}