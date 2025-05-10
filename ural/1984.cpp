#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    if (n==1) cout << 1 << endl;
    else {
        cout << setprecision(8) << fixed;
        cout << 1 / cos(acos(-1) * (n-2) / (2*n)) + 1 << endl;
    }
    return 0;
}