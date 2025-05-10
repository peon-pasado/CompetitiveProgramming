#include <bits/stdc++.h>
using namespace std;
string s;
void print(int a, int b = -1) {
	int x = -1, y = -1;
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] % 3 == a) x = i;
	}
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] % 3 == b) {
			if (a == b) {
				if (x != i) y = i;
			} else y = i; 
		}
	}
	for (int i = 0; i < s.size(); ++i) {
		if (x == i or y == i) continue;
		putchar(s[i]);
	} puts("");
}

int main() {
	cin >> s;
	int dig[3] = {0};
	for (auto c : s) {
		dig[c%3] += 1;
	}
	int sum = 0;
	for (int i = 1; i < 3; ++i) {
		sum = (sum + i * dig[i])%3;
	}
	if (sum == 0) cout << s << endl;
	else {
		if (s.size() == 1) cout << -1 << endl;
		else if (dig[sum] > 0) {
			if (dig[sum] == 1 and s[0]%3 == sum) {
				if (s[1] == '0') {
					if (s.size() == 2) puts("0"); 
					else if (dig[3 - sum] >= 2) {
						print(3 - sum, 3 - sum);
					} else {
						bool ok = 0;
						for (int i = 1; i < s.size(); ++i) {
							if (s[i] != '0') ok = 1;
							if (ok) putchar(s[i]);
						}
						if (not ok) printf("0");
						puts("");
					}	
				} else print(sum);
			} else print(sum);
		} else {
			if (s.size() == 2) puts("-1");
			else if (dig[3 - sum] < 2) puts("-1");
			else if (dig[3 - sum] == 2) {
				bool open = 0;
				bool ok = 0;
				for (int i = 0; i < s.size(); ++i) {
					if (open and s[i] == '0') continue;
					if (s[i] % 3 == 3 - sum) {
						open = not ok;					
						continue;
					}
					open = 0;
					ok = 1;
					putchar(s[i]);
				}	
				if (ok) puts("");
				else puts("0");
			} else print(3 - sum, 3 - sum);
		}	
	}
	return 0;
}