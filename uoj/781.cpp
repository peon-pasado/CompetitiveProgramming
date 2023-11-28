#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
long long a[maxn];

/**
 * asumamos a1 <= a2 <= ... <= an
 * 
 * sean los puntos seleccionados p1, p2, ..., pn
 * y sea bi = |pi|
 * 
 * queremos resolver sum ai bi >= 2 * max(ai bi),
 * 
 * sea S' = a1 + ... + an-1
 * 
 * S' * (r + i) >= an * r 
 * 
 * se cumple:
 * 
 *  - an-1 * x <= an * r
 *  - r <= x <= R
 * 
 * por tanto:
 * 
 *  - x <= min(R, an * r / an-1) 
 * 
 *  - sum min(ai * R, an * r) >= an * r
 * 
 * como solo se necesita que un lado derecho del maximo 
 * se cumpla, basta ver que:
 * 
 * answer: [R sum ai >= an * r]
**/

int main() {
    int n, r, R;
    cin>>n>>r>>R;
    for (int i=0; i<n; ++i) {
        cin>>a[i];
    }
    sort(a, a+n);
    long long sum = 0;
    for (int i=0; i<n-1; ++i) sum += a[i];
    if (a[n-1] * r <= sum * R) cout << "YES" << '\n';
    else cout << "NO" << '\n';
    return 0;
}