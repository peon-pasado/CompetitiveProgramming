#include <bits/stdc++.h>
using namespace std;

int main() {
	long long a[3];
	for (int i = 0; i < 3; ++i) {
		cin >> a[i];
	}
	long long s = 2 * a[1] - a[0] - a[2];
	long long ans = 0;
	if (s > 0) ans = s;
	else if (s < 0) {
		s = abs(s);
		if (s%2 == 0) ans = s/2;
		else ans = (s+1)/2 + 1;
	}
	cout << ans << '\n';
	return 0;
}