#include <iostream>
#include <vector>
using namespace std;

const int maxn = 2e6 + 10;
bool comp[maxn];
int cnt[maxn], ways[maxn], ex[maxn];
vector<int> pr;

void sieve() {
	for (int i = 2; i < maxn; ++i) {
		if (!comp[i]) {
			pr.push_back(i);
			cnt[i] = 1;
			ways[i] = 1;
			ex[i] = 1;
		}
		for (int j = 0; j < pr.size(); ++j) {
			if (pr[j] * i >= maxn) break;
			comp[pr[j] * i] = 1;
			cnt[pr[j] * i] = cnt[i] + 1;
			if (i % pr[j] == 0) {
				ex[pr[j] * i] = ex[i] + 1;
				ways[pr[j] * i] = ways[i] * cnt[pr[j] * i] / ex[pr[j] * i];
				break;
			} else {
				ex[pr[j] * i] = 1;
				ways[pr[j] * i] = ways[i] * cnt[pr[j] * i] / ex[pr[j] * i];
			}
		}
	}
}

int main() {
	sieve();
	int n;
	while (cin >> n) {
		cout << cnt[n] << ' ' << ways[n] << '\n';
	}
	return 0;
}