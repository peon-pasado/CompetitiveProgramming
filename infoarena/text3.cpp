/**
 * @author Miguel Mini
 * @tag lis
 * @idea 
 *      - we can see that to eliminate 
 *      the minimum amount of words we
 *      can find the LIS of the words.
 * 
 *      - we can reduce the complexity 
 *      from O(n^2) to O(n + sigma) if 
 *      we save best states for each 
 *      character.
 * 
 * @complexity O(n + sigma)
 */ 


#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("text3.in", "r", stdin);
	freopen("text3.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<string> sv;
	string s;
	while (cin >> s) {
		sv.emplace_back(s);
	}
	int n = sv.size();
	cout << n << '\n';
	vector<int> dp(n);
	int last[30];
	memset(last, -1, sizeof last);
	for (int i = 0; i < n; ++i) {
		int l = sv[i][0] - 'a';
		int r = sv[i].back() - 'a';
		if (~last[l]) {
			dp[i] = dp[last[l]] + 1;
		} else {
			dp[i] = 1;
		}
		if (last[r] == -1 || dp[last[r]] < dp[i]) {
			last[r] = i;
		}
	}
	int pos = max_element(dp.begin(), dp.end()) - dp.begin();
	cout << n - dp[pos] << '\n';
	int ans = dp[pos];
	vector<int> res;
	char last_ch = sv[pos].back();
	for (int i = n-1; i >= 0; --i) {
		if (sv[i].back() == last_ch && dp[i] == ans) {
			res.push_back(i);
			ans -= 1;
			last_ch = sv[i][0];
		}
	}
	reverse(res.begin(), res.end());
	for (int i : res) {
		cout << sv[i] << '\n';
	}
	return 0;
}