#include <iostream>
using namespace std;

bool is_prime(int n) {
    if (n <= 2) return 0;
    for (int i=2; i*i<=n; ++i) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int main() {
    int n;
    int t = 1;
    while (cin>>n, n>0) {
        cout << t++ << ": " << (is_prime(n) ? "yes" : "no") << '\n';
    }
    return 0;   
}