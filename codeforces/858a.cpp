#include <bits/stdc++.h>
using namespace std;

int main() {
	long long x ,k;
	cin >> x >> k;
        long long ten = 1;
        for (int i = 0; i < k; ++i) ten *= 10;
        cout << x * ten / __gcd(x, ten) << endl; 
	return 0;
}