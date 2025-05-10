#include <iostream>
using namespace std;

int gcdex(int a, int b, int& x, int& y) {
    if (b == 0) {
        x=1; y=0;
        return a;
    }
    int x0, y0, g = gcdex(b, a%b, x0, y0);
    x = y0;
    y = x0 - y0 * (a/b);
    return g;
}

int main() {
    int x, y, m, n, L;
    cin>>x>>y>>m>>n>>L;
    int A = (x-y) % L;
    int B = (n-m) % L;
    if (A < 0) A += L;
    if (B < 0) B += L;
    //A = k * B + t L
    int x0, y0, g = gcdex(B, L, x0, y0);
    if (A % g != 0) return cout<<"Impossible"<<'\n', 0;
    A /= g; L /= g;
    //k = x0 * A + z L;
    int k = 1LL * x0 * A % L;
    if (k < 0) k += L;
    cout << k << '\n';
    return 0;
}