#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin>>n;
    while (n % 2 == 0) n /= 2;
    while (n % 3 == 0) n /= 3;
    cout << (n == 1 ? "Yes" : "No") << '\n'; 
    return 0;
}