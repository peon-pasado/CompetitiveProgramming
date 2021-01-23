/**
 *  @author Miguel Mini
 *  @tag two_pointers, sorting, constructive
 *  @tag:
 *      - we add the cubes from largest to 
 *      smallest size
 *
 *      - we can place each new block on top,
 *      or below each j block with:
 *          a[j] <= new_block + d
 *
 *      - the answer is prod (j - i + 1)
 *      for all i and j the largest value 
 *      that meets a[j] <= a[i] + d.
**/

#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, d;
	cin >> n >> d;
	vector<int> a(n);
	for (auto& x : a) cin >> x;
	sort(a.begin(), a.end());
	long long ans = 1;
	const int mod = 1e9 + 9;
	for (int i = 0, j = 0; i < n; ++i) {
		while (j + 1 < n && a[j + 1] <= a[i] + d) j += 1;
		ans = ans * (j - i + 1) % mod;
	}
	cout << ans << endl;
	return 0;
}
