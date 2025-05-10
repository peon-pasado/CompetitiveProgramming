#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e5 + 10;
int a[maxN];
vector<int> bin[maxN];
int f[maxN];
int n;

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	int len = 1000;
	for (int i = 1; i <= n; ++i) {
		while (a[i] > 0) {
			bin[i].push_back(a[i]&1);
			a[i] >>= 1;
		}
		reverse(begin(bin[i]), end(bin[i]));
		len = min(len, (int)bin[i].size());
	}	
	int id = 0;
	for (int j = 1; j < len; ++j) {
		bool ok = 1;
		for (int i = 2; i <= n; ++i) {	
			if (bin[i][j] != bin[i-1][j]) {
				ok = 0;
				break;
			}	
		}
		if (ok) id = j;
		else break;
	}
	for (int i = 1; i <= n; ++i) {
		reverse(begin(bin[i]), end(bin[i]));
		for (int j = 0; j <= id; ++j) bin[i].pop_back();
		for (int j = (int)bin[i].size() - 1; j >= 0; --j) {	
			if (bin[i][j] == 0) f[i] += 1;
			else break;
		}
	}
	int ans = INT_MAX;
	for (int k = 0; k < 100; ++k) {
		int lans = 0;
		for (int i = 1; i <= n; ++i) {
			if (k <= f[i]) lans += (int)bin[i].size() - k;
			else lans += (int)bin[i].size() + k - 2*f[i]; 
		}
		ans = min(ans, lans);
	}
	cout << ans << endl;
	return 0;
}