#include <iostream>
#define ll long long
using namespace std;

ll gcdex(ll a, ll b, ll& x, ll& y) {
    if (!b) return x=1, y=0, a;
    ll g = gcdex(b, a%b, y, x);
    return y -= a/b*x, g;
}


ll A, B, C, k, L;
inline ll modL(ll x) { return x % L + (x<0) * L;}

int main() {
    while (cin>>A>>B>>C>>k, k>0) {
        L = 1LL<<k; 
        //A + kC = B (mod 2^k)
        //B - A = kC + t L
        ll Z = modL(B-A);    
        ll x0, y0, g = gcdex(C, L, x0, y0);
        if (Z % g != 0) {
            cout<<"FOREVER"<<'\n';
            continue;
        }
        Z /= g; L /= g;
        ll k = modL(x0 * Z);
        cout << k << '\n';
    }
    return 0;
}