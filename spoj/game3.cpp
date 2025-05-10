#include <iostream>
using namespace std;
const int maxN = (1<<26)+1;

long long h(int n) {
	if (n == 0) return 0;
	n -= 1;
	return (8 * (1ll<<(n+n)) - 6 * (1ll<<n) + 1) / 3; 
}

long long g(int n) {
	if (n == 0) return 0;
	long long ans = 0;
	for (int i = 27; i >= 0; --i) {
		if (n & (1<<i)) {
			ans += h(i+1) - h(i);
		}
	}
	return ans;
}

long long f(int n) {
	return (n + 1) / 2 + g(n/2);
}

int main() {
	int t; cin >> t;
	while (t--) {
		long long n; cin >> n;
		int lo = 0, hi = maxN-1;			
		while (lo < hi) {		
			int mid = lo + (hi - lo) / 2;
			if (f(mid) < n) lo = mid + 1;
			else hi = mid;
		}
		cout << ((lo&1) ? "Ivica" : "Marica") << endl;
	}
	return 0;	
}
