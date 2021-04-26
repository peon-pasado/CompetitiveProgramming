/**
 * @author Miguel Mini
 * @tag dp, win-lose
 * @idea
 *      - number of states
 *      is small. 
 * 
 *          O(log(n)^4 / (log(2) * log(3) * log(5) * log(7)))
 * 
 *          ~ O(log(n)^4 / 10)
 * 
 * @complexity O(log(n)^4)
 */ 

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
map<ll, bool> dp;
bool bt(ll p, ll n) {
	if (p >= n) return 0;
	if (dp.count(p)) return dp[p]; 
	bool ans = 0;
	for (int t = 2; t <= 9; ++t) {
		if (!bt(p * t, n)) {
			ans = 1;
			break;
		}
	}
	dp[p] = ans;
	return ans;
}

int main() {
	long long n;
	while (cin >> n) {
		dp.clear();
		if (bt(1, n)) {
			cout << "Stan wins." << '\n';
		} else {
			cout << "Ollie wins." << '\n';
		}
	}
	return 0;
}