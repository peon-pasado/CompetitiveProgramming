#include <bits/stdc++.h>
using namespace std;

const int maxn = 18;
using ll = long long;
using ii = pair<int, int>;
ll F[maxn][1<<maxn];
int cnt[maxn];
string s;

int main() {
	int n, k;
	cin >> n >> k;
	cin >> s;
	for (auto& c : s) cnt[c -= 'a']++;
	for (int i = 0; i < k; ++i) {
		vector<ii> blocks;
		for (auto c : s) {
			if (c == i) {
				for (auto e : blocks)
					F[i][e.first] += e.second;
			}
			
			for (auto& e : blocks)
				e.first |= (1<<c);
				
			if (c == i) blocks.emplace_back(1<<c, 1);
			
			int m = 1;
			for (int j=1; j<blocks.size(); ++j) {
				if (blocks[m-1].first == blocks[j].first) 
					blocks[m-1].second += blocks[j].second;
				else
					blocks[m++] = blocks[j];
			}
			blocks.resize(m);
		}
		for (int j=0; j<k; ++j)
			for (int s=0; s<1<<k; ++s)
				if (s&(1<<j))
					F[i][s] += F[i][s^(1<<j)];
	}
	int q;
	cin >> q;
	while (q--) {
		string u;
		cin >> u;
		int mask = 0;
		for (auto& e : u) {
			e -= 'a';
			mask |= (1<<e);
		}
		ll ans = 0;
		for (int i = 0; i < k; ++i) {
			if (~mask & (1<<i)) {
				ans += 2 * F[i][mask | (1<<i)] + cnt[i];
			}
		}
		cout << ans << '\n';
	}
	return 0;
}