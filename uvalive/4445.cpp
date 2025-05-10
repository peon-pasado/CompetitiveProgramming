#include <bits/stdc++.h>
using namespace std;

int n, nc=1;
pair<int, int> P[10];
int id[10];

bool p(int x) {
	int last = P[id[0]].first;
	for (int i = 1; i < n; ++i) {
		int e = id[i];
		int pos = last + x;
		if (P[e].second < pos) return 0;
		last = max(pos, P[e].first);
	}
	return 1;
}


int main() {

	while(cin >> n, n) {
		for (int i = 0; i < n; ++i) {
			cin >> P[i].first >> P[i].second;
			P[i].first *= 600;
			P[i].second *= 600;
		}
		
		for (int i = 0; i < n; ++i)
			id[i] = i;

		int ans = 0;
		while (true) {
			int lo = 0, hi = 1440 * 60 * 10;
			while (lo < hi) {
				int mid = lo + (hi-lo+1)/2;
				if (p(mid)) lo = mid;
				else hi = mid-1;
			}		
			if (p(lo))
				ans = max(ans, lo);
		
			if (not next_permutation(id, id+n)) break;
		}


		cout << "Case " << nc++ << ": ";
		int h = ans/600;
		int m = (ans%600 + 5)/10;
		if (m==60) h += 1, m = 0;
		printf("%d:%02d\n", h, m);
	}

	return 0;
}