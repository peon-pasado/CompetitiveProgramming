#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin >> t;
	while (t--) {
		int a, b, c;
		cin >> a >> b >> c;
		int x = -1;
		for (int i = 1000; i <= 9999; ++i) {	
			if (i % a == 0 and i % b == b-1 and i % c == c-2) {
				x = i;
				break;
			}
		}
		if (x != -1) {
			cout << x << endl;
		} else {
			cout << "Impossible" << endl;
		}
	}	
	return 0;
}