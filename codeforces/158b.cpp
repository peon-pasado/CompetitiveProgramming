#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	int cnt[5] = {0};
	for (int i = 0; i < n; ++i) {
		int si;
		cin >> si;
		cnt[si] += 1;
	}
	int res = 0;
	res += cnt[4];
	res += cnt[3];
	cnt[1] = max(0, cnt[1] - cnt[3]);
	res += cnt[2] / 2;
	cnt[2] %= 2;
	res += (cnt[1] + cnt[2] * 2 + 4 - 1) / 4;
	cout << res << '\n';
	return 0;
}