#include <iostream>
using namespace std;

int main() {
int t;
cin >> t;
while (t--) {
int n;
cin >> n; 
long long sum = 0;
for (int i = 1; i <= n; ++i) {
long long x; 
cin >> x;
sum += x;
}
cout << sum << endl;
if (t > 0) cout << endl;
}
return 0;
}