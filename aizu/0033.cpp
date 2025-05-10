#include <iostream>
using namespace std;

int main() {
	int t;
	cin >> t;
	while (t--) {
		bool valid = 1;
		int l = 0, r = 0;
		for (int i = 0; i < 10; ++i) {
			int balon;
			cin >> balon;
			if (l < balon && r < balon) {
				if (l > r) l = balon;
				else r = balon;
			} else if (l < balon) {
				l = balon;
			} else if (r < balon) {
				r = balon;
			} else {
				valid = false;
			}
		}
		if (valid) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}