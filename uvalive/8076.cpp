#include <bits/stdc++.h>
using namespace std;
const int maxN = 20;
int u[maxN], r[maxN], a[maxN], b[maxN], t[maxN];

int main() {
	while (cin >> u[0] >> r[0]) {
		for (int i = 1; i < 10; ++i) {
			cin >> u[i] >> r[i];
		}
		for (int i = 0; i < 10; ++i) {
			cin >> a[i] >> b[i] >> t[i];
		}
		int time = 0;
		for (int i = 0; i < 30; ++i) {
			if (time < t[i%10]) {
				time += u[i%10] + r[i%10];
				t[i%10] = max(t[i%10], time - r[i%10]);
			} else {
				while (t[i%10] + a[i%10] + b[i%10] <= time) t[i%10] += a[i%10] + b[i%10];
				time = max(time, t[i%10] + a[i%10]);
				time += u[i%10] + r[i%10];
				t[i%10] = max(t[i%10] + a[i%10] + b[i%10], time - r[i%10]);
			}
		}
		cout << time - r[9] << endl;
	}
	return 0;
}