#include <bits/stdc++.h>
using namespace std;

int main() {
	string a, b;
	cin >> a >> b;
	bool ans;
	if (a.size() != b.size()) {
		ans = 0;
	} else {
		int n = a.size();
		string c(n, '0');
		if (a == c and b == c) ans = 1;
		else if (a == c or b == c) ans = 0;
		else ans = 1;
	}
	if (ans) cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}