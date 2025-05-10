#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
const int maxN = 1e5 + 10;
int x[maxN];
int n;
int a, b, d;

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", x+i);
	}
	scanf("%d %d", &a, &b);
	sort(x, x+n);
	n = unique(x, x+n) - &x[0];
	vector<int> v;
	for (int i = 0; i < n; ++i) v.push_back(x[i]);
	int ans = 0;
	while (not v.empty()) {
		if (a == b) break;
		vector<int> v2;
		int mi = a;
		for (int e : v) {
			int d = a / e * e;
			if (d >= b) {
				mi = min(mi, d);		
			} 
		}

		if (a == mi) ans += 1, a -= 1;
		else ans += 1, a = mi;

		for (int e : v) {
			int d = a / e * e; 
			if (d >= b) {			
				v2.push_back(e);
			}
		}
		v = v2;
	}

	cout << ans + a - b << endl;
	return 0;
}