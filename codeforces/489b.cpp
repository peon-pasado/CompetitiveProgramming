#include<bits/stdc++.h>
using namespace std;

const int maxn = 110;
multiset<int> a, b;

int main() {
	int n, m;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		a.insert(x);
	}
	cin >> m;
	for (int i = 0; i < m; ++i) {
		int x;
		cin >> x;
		b.insert(x);
	}
	int ans = 0;
	while (true) {
		if (a.empty() || b.empty()) break;
		if (*a.begin() < *b.begin()) { //comparar minimos
			if (abs(*a.begin() - *b.begin()) > 1) a.erase(a.begin()); //eliminar minimo
			else {
				ans += 1;
				a.erase(a.begin());
				b.erase(b.begin());
			}
		} else {
			if (abs(*a.begin() - *b.begin()) > 1) b.erase(b.begin());
			else {
				ans += 1;
				a.erase(a.begin());
				b.erase(b.begin());
			}
		}
	}
	cout << ans << endl;
	return 0;
}