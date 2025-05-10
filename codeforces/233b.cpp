#include <bits/stdc++.h>
using namespace std;

int main() {
	long long n;
	cin >> n;
	auto d = [](long long x) {
    int sum = 0;
    while (x > 0) {
      sum += x % 10;
      x /= 10;
    }
  	return sum;
  };
	int sq = sqrt(n);
	for (long long x = max(1, sq - 90); x <= sq; ++x) {
		if (x*x + d(x)*x - n == 0) {
			cout << x << '\n';
			return 0;	
		}
	}
	cout << -1 << '\n';
	return 0;
}