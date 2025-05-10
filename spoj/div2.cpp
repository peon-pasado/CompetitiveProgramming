#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
int di[maxn];
bool can[maxn];
vector<int> f;

void sieve(int n) {
	for (int i = 1; i <= n; ++i) {
		for (int j = i; j <= n; j += i) {
			di[j] += 1;
		}
	}
	for (int i = 1; i <= n; ++i) can[i] = di[i] > 3;
	for (int i = 1; i <= n; ++i) {
		for (int j = i; j <= n; j += i) {
			if (can[j] and di[j] % di[i]) can[j] = 0;
		}
		if (can[i]) f.emplace_back(i);
	}
}

int main() {
	sieve(1e6);
	for (int i = 107; i < f.size(); i += 108) {
		printf("%d\n", f[i]);
	}
	return 0;
}