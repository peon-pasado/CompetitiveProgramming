#include <bits/stdc++.h>
using namespace std;

int rotate(int c, int k) {
	c -= 'A';
	c += k;
	c %= 26;
	return c + 'A';
}
int num[500];

string process(string s) {
	int sum = 0;
	for (auto c : s) sum += num[c];
	for (auto& c : s) c = rotate(c, sum);
	return s;
}

int main() {
	for (int i = 0; i < 26; ++i) {
		num['A' + i] = i;
	}
	string s;
	while (cin >> s) {
		int n = s.size();
		string A = process(s.substr(0, n/2));
		string B = process(s.substr(n/2, n/2));
		for (int i = 0; i < n/2; ++i) {
			cout << (char)rotate(A[i], B[i] - 'A');
		}
		cout << endl;
	}
	return 0;
}