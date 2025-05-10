#include <bits/stdc++.h>
using namespace std;

const int maxn = 18;
int A[1<<maxn], F[1<<maxn];
int n, m, k;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m >> k;
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		A[x] += 1;
	}
	for (int s = 0; s < 1<<k; ++s)
				F[s] = A[s];
	for (int l = 0; l < k; ++l)
		for (int s = 0; s < 1<<k; ++s)
			if (~s & (1<<l))
				F[s] += F[s^(1<<l)];
	
	int B = 512;
	vector<pair<int, int>> sack;
	for (int i = 0; i < m; ++i) {
		int type;
		int v;
		cin >> type >> v;
		if (sack.size() == B) {
			for (int s = 0; s < 1<<k; ++s)
				F[s] = A[s];
			for (int l = 0; l < k; ++l)
				for (int s = 0; s < 1<<k; ++s)
					if (~s & (1<<l))
						F[s] += F[s^(1<<l)];
			sack.clear();
		}
		
		if (type == 1) A[v] += 1, sack.push_back({v, 1});
		if (type == 2) A[v] -= 1, sack.push_back({v, -1});
		if (type == 3) {
			int ans = 0;
			for (int l = k-1; l >= 0; --l) {
				int mask = ans ^ (1<<l);
				int cnt = F[mask];
				for (auto e : sack)
					if ((e.first & mask) == mask) cnt += e.second;
				if (cnt >= v) ans ^= (1<<l);
			}
			cout << ans << '\n';
		}
	}
	return 0;
}