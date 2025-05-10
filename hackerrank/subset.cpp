#include <bits/stdc++.h>
using namespace std;

const int maxn = 16;
int F[1<<maxn];
int A[1<<maxn];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int q;
	cin >> q;
	vector<pair<int, int>> queries;
	int B = 1<<11;
	for (int i = 0; i < q; ++i) {
		string s;
		int d;
		cin >> s >> d;
		if (queries.size() == B) {
			queries.clear();
			for (int s = 0;  s < 1<<16; ++s)
				F[s] = A[s];
			for (int j = 0; j < 16; ++j) {
				for (int s = 0; s < 1<<16; ++s) {
					if (s&(1<<j))
						F[s] += F[s^(1<<j)];
				}
			}
		}
		if (s[0] == 'c') {
			int ans = F[d];
			for (auto e : queries)
				if ((d&e.first) == e.first) 
					ans += e.second;
			cout << ans << '\n';
		} else if (s[0] == 'd') {
			A[d]--;
			queries.push_back({d, -1});	
		} else {
			A[d]++;
 			queries.push_back({d, 1});
		}
	}
	return 0;
}