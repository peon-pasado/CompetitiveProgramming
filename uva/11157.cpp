#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	scanf("%d\n", &t);
	for (int tc = 1; tc <= t; ++tc) {
		int n, d;
		scanf("%d %d\n", &n, &d);
		vector<int> arr(n + 2);
		for (int i = 0; i < n; ++i) {
			char c;
			int pos;
			scanf("%c-%d%*c", &c, &pos);
			if (c == 'S') arr[i] = -pos;
			else arr[i] = pos;
		}
		arr[n] = 0;
		arr[n+1] = d;
		printf("Case %d: ", tc);
		sort(arr.begin(), arr.end(), [](int x, int y) {
			return abs(x) < abs(y);
		});
		int last = 0;
		int ans = 0;
		for (int i = 0; i < arr.size(); ++i) {
			if (arr[i] >= 0) {
				int lans = 0;
				lans = max(lans, abs(arr[last + 1]) - abs(arr[last]));
				if (last + 2 <= i) {
					lans = max(lans, abs(arr[last + 2]) - abs(arr[last]));
				}
				lans = max(lans, abs(arr[i]) - abs(arr[i - 1]));
				if (i - 2 >= last) {
					lans = max(lans, abs(arr[i]) - abs(arr[i - 2]));
				}
				for (int j = last + 3; j < i; j += 2) {
					lans = max(lans, abs(arr[j]) - abs(arr[j-2]));	
				}
				for (int j = last + 4; j < i; j += 2) {
					lans = max(lans, abs(arr[j]) - abs(arr[j-2]));
				}
				ans = max(ans, lans);
				last = i;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}