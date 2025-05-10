#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e5 + 10;
int l[maxN], r[maxN];

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> l[i] >> r[i];
	}
	sort(l, l+n);
	sort(r, r+n);
	long long sum = 0;
	for (int i = 0; i < n; ++i) {
		sum += 1 + max(l[i], r[i]);
	}
	cout << sum << endl;
	return 0;
}