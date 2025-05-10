#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;

int ex(int a, long long b) {
	int r = 1;
	while (b > 0) {
		if (b&1) r = r*1ll*a%mod;
		a = a*1ll*a%mod;
		b >>= 1;
	}
	return r;
}

int main() {
	int n, x;
	cin >> n >> x;
	vector<int> a(n);
	for (int& v : a) cin >> v;
	long long sum = accumulate(a.begin(), a.end(), 0ll);
	map<long long, int> t;
	for (int v : a) t[sum - v] += 1; 
 	while (true) {
		vector<pair<long long, int>> temp;
		for (auto e : t) {
			if (e.second % x == 0) {
				temp.push_back(e);
			}
		}
		if (temp.empty()) break;
		for (auto e : temp) {
			t[e.first + 1] += t[e.first] / x;
			t.erase(e.first);
		}
	}
	long long e = t.begin()->first;
	e = min(e, 1ll*sum);
	cout << ex(x, e) << endl;
	return 0;
}