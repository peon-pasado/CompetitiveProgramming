#include <bits/stdc++.h>
using namespace std;

class RareItems {
public:
	int n;
	int sum;
	int target;
	bool vis[1500000];
	double memo[1500000];
vector<int> f;
	double dp(int mask) {
		if (mask == target) return 0;	
		if (vis[mask]) return memo[mask];
		vis[mask] = 1;
		double num = sum;
		double den = 0;
		for (int i = 0; i < n; ++i) {
			if (~mask & (1<<i)) {
				den += f[i];
				num += f[i] * dp(mask | (1<<i));
			}
		}
		return memo[mask] = num / den;
	}
	double expectedPurchases(vector<int> frequency)	{
		n = frequency.size();
f = frequency;
		target = (1<<n)-1;
		sum = accumulate(begin(frequency), end(frequency), 0);
		return dp(0);
	}
} TEST;

//int main() {cout << TEST({1, 2, 3}) << endl; return 0;}