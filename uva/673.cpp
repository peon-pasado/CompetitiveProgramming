#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin >> t;
	cin.get();
	for (int i = 0; i < t; ++i) {
		string s;
		getline(cin, s);
		stack<char> p;
		bool good = true;
		for (auto c : s) {
			if (c == '(' || c == '[') {
				p.push(c);
			} else if (!p.empty()) {
				if ((c == ')' && p.top() == '(') || (c == ']' && p.top() == '[')) {
					p.pop();
				} else {
					good = false;	
				} 
			} else {
				good = false;
			}
			if (!good) {
				break;
			}
		}
		if (!p.empty()) good = false;
		if (good) cout << "Yes" << '\n';
		else cout << "No" << '\n';
	}
	return 0;
}