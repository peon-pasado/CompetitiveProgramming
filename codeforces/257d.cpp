#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e5 + 10;
int ans[maxN];
int a[maxN];
bool res[maxN];
int n;

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	long long s = 0;
	for (int i = 1; i <= n; ++i) {
		if (s + a[n-i+1] > a[1]) {
			if (s - a[n-i+1] >= 0) {		
				ans[i] += 1;
				ans[i+1] += 1;
				s = s - a[n-i+1];
			} else {
				ans[1] += 1;
				ans[i] += 1;
				s = a[n-i+1] - s;
			}
		} else {
			s = s + a[n-i+1];
		}
	}	
	for (int i = 1; i <= n; ++i) {
		ans[i] += ans[i-1];
		res[n-i+1] = (ans[i]%2);
	}
	for (int i = 1; i <= n; ++i) {
		cout << (res[i] ? "-" : "+");
	} cout << endl;
	return 0;
}