#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	sort(a.rbegin(), a.rend());
	queue<int> Q;
	Q.push(0);
	long long ans = 0;
	for (int i = 0; i < n; ++i) {
		int q = Q.front(); Q.pop();
		ans += q;
		if (i) Q.push(a[i]);
		Q.push(a[i]);
	}
	cout << ans << endl;
	return 0;
}