#include <bits/stdc++.h>
using namespace std;

int n;
long long get(string& a, int pos = 0, bool p = 0, int m = n) {
	if (pos == a.size()) return 0;
	if (a[pos] == p + '0') return get(a, pos+1, 0, m-1);
	return get(a, pos+1, 1, m-1) + (1ll<<m-1);
}

int main() {
	string a, b;
	while (cin >> n >> a >> b) {
		long long ans;
		if (a == b) cout << 0 << endl;
		else {
			long long pa = get(a), pb = get(b);
			cout << max(pa - pb - 1, pb - pa - 1) << endl;
		} 
	}
	return 0;
}