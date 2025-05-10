#include <iostream>
using namespace std;

const int maxn = 18;
int a[1<<maxn];
int F[1<<maxn][2];

void update(int m, int v) {
	if (F[m][0] <= v) {
		F[m][1] = F[m][0];
		F[m][0] = v;
	} else {
		F[m][1] = max(F[m][1], v);
	}
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < 1<<n; ++i) {
		cin >> F[i][0];
		F[i][1] = -1e9;
	}
	for (int i = 0; i < n; ++i)
		for (int s = 0; s < 1<<n; ++s)
			if (s&(1<<i)) {
				update(s, F[s^(1<<i)][0]);
				update(s, F[s^(1<<i)][1]);
			}
	int ans = -1e9;
	for (int i = 1; i < 1<<n; ++i) {
		ans = max(ans, F[i][0]+F[i][1]);
		cout << ans << '\n';
	}
	return 0;
}