#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;
bool comp[maxn];
int cnt[maxn];
vector<int> pr;

void sieve() {
	for (int i = 2; i < maxn; ++i) {
		cnt[i] = cnt[i-1];
		if (!comp[i]) {
			pr.push_back(i);
			cnt[i]++;
		}
		for (int p : pr) {
			if (p * i >= maxn) break;
			comp[p * i] = 1;
			if (i % p == 0) break;
		}
	}
}

int main() {
	sieve();
	int n;
	while (cin >> n) {
		cout << cnt[n] << '\n';
	}
	return 0;
}