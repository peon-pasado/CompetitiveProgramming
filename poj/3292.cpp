#include <iostream>
using namespace std;

const int maxn = 1e6 + 10;
bool comp[maxn];
int sum[maxn];

int main() {
	for (int i = 5; i < maxn; i += 4) {
		if (!comp[i]) {
			for (int j = 5; i * j < maxn; j += 4) {
				comp[i * j] = 1;
				if (j <= i && !comp[j]) sum[i * j] = 1;
			}
		}
	}
	for (int i = 1; i < maxn; ++i) sum[i] += sum[i-1];
	int n;
	while (cin >> n, n) {
		cout << n << ' ' << sum[n] << '\n';
	}
	return 0;
}