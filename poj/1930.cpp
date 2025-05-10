#include <iostream>
#include <cstring>
#include <utility>
#include <cstdlib>
using namespace std;

bool period(string& s, int l, int r) {
	int pos = s.size() - l - r;
	for (int i = 0; i < r; ++i)
		if (s[pos+i] != s[pos+l+i]) 
			return 0;	
	return 1;
}

int gcd(int a, int b) {
	return b==0?a:gcd(b, a%b);
}

int main() {
	int ten[20] = {1};
	for (int i = 1; i < 10; ++i) {
		ten[i] = ten[i-1] * 10;
	}
	string s;
	while (cin >> s, s != "0") {
		int n = s.size() - 5;
		s = s.substr(2, n);
		pair<int, int> ans = pair<int, int>(2e9, 0);
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < i && j + i <= n; ++j) {
				if (period(s, i, j)) {
					int m = n - i - j;
					int num = atoi(s.substr(0, m+i).c_str()) - atoi(s.substr(0, m).c_str());
					int den = ten[m+i] - ten[m];
					
					//s*10^{m+i} = s[0] s[1] ... s[m-1] (s[m] s[m+1], ..., s[m+i-1]).
					//s*10^m     =                              s[0] s[1] ... s[m-1].
					//s * (10^{m+i} - 10^m) = atoi(s.substr(0, m+i)) - atoi(s.substr(m))
					
					int g = gcd(num, den);
					num /= g;
					den /= g;
					ans = min(ans, pair<int, int>(den, num));
				}
			}
		}
		cout << ans.second << "/" << ans.first << '\n';
	}
	return 0;
}