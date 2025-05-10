#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	vector<int> nxt(n), prv(n);
	stack<int> L;
	for (int i = 0; i < n; ++i) {
		while (!L.empty() && a[L.top()] >= a[i]) L.pop();
		if (L.empty()) prv[i] = -1;
		else prv[i] = L.top();
		L.push(i);
	}
	stack<int> R;
	for (int i = n-1; i >= 0; --i) {
		while (!R.empty() && a[R.top()] >= a[i]) R.pop();
		if (R.empty()) nxt[i] = n;
		else nxt[i] = R.top();
		R.push(i);
	}
	long long ans = 0;
	for (int i = 0; i < n; ++i) {
		ans = max(ans, a[i] *1ll* (nxt[i] - prv[i] - 1));
	}
	cout << ans << endl;
	return 0;
}