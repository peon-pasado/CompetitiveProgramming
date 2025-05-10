#include <bits/stdc++.h>
using namespace std;
bool vis[55];
int n;
vector<int> d;
void solve(int pos, long long m, int cur) {
	pos = max(pos, 0);
	if (cur == n) {
		for (int i = n; i >= 1; --i) {
			if (!vis[i]) d.push_back(i);
		}
		return;
	}
	if ((1ll<<pos) <m) {
		solve(pos-1, m - (1ll<<pos), cur+1);
	} else {
		vis[cur] = 1;
		d.push_back(cur);
		solve(pos-1, m, cur+1);
	}
}

int main() {
	long long m;
	cin >> n >> m;
	solve(n-2, m, 1);
	for (int v : d) cout << v << " "; cout << endl;
	return 0;
}