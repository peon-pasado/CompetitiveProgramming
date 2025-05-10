#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	int res = 0;
	for (int i = 0; i < n; ++i) {
		int a;
		int b;
		int c;
		cin >> a >> b >> c;
		if ((a + b + c) > 1) {
			res += 1; 
		}
	}	
	cout << res << '\n';
	return 0;
}