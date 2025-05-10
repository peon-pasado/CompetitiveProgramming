#include <bits/stdc++.h>
using namespace std;

int main() {
	long long n, s;
	cin >> n >> s;
	auto d = [](long long x) {
            int sum = 0;
            while (x > 0) {
                sum += x % 10;
                x /= 10;
            }
  	    return sum;
        };
	//[s, s + 161][s + 162, n]
	long long cnt = max(n - (s + 162) + 1, 0ll);
	for (long long x = s; x <= min(s+161, n); ++x) {
		if (x - d(x) >= s) {
			cnt++;
		}
	}
	cout << cnt << '\n';
	return 0;
}