#include <iostream>
using namespace std;

int main() {
	int n;
	string s;
	cin >> n >> s;
	int cnt = 0;
	for (int i = 0; i+1 < n; ++i) {
		cnt += s[i] == s[i+1];
	}
	cout << cnt << endl;
	return 0;
}