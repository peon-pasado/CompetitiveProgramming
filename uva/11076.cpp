#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	while (cin >> n && n != 0) {
		int arr[15];
		for (int i = 0; i < n; ++i) {
			cin >> arr[i];
		}
		unsigned long long f[20];
		f[0] = 1;
		for (int i = 1; i < 15; ++i) {
			f[i] = f[i-1] * i;
		}
		int sm = 0;
		for (int i = 0; i < n; ++i) {
			sm += arr[i];
		}
		int oc[12];
		for (int i = 0; i < 10; ++i) {
			oc[i] = 0;
		}
		for (int i = 0; i < n; ++i) {
			oc[arr[i]] += 1;
		}
		unsigned long long M = f[n];
		for (int i = 0; i < 10; ++i) {
			M /= f[oc[i]];
		}
		unsigned long long tm = 1;
		for (int i = 0; i < n; ++i) {
			tm *= 10;
		}
		tm -= 1;
		tm /= 9;
		unsigned long long ans = M * sm / n * tm;
		cout << ans << endl;
	}
	return 0;
}