/***
 * @idea
 *      - si n >= k, la rpta es n-k.
 *      - +1 y -1 no se intercalan.
 *      - solo al final conviene aumentar muchos 1s o -1s.
 *      - a menos que no sea el final, es mejor multiplicar x2.
**/

#include <iostream>
#include <cstring>
#include <queue>
#include <bitset>
using namespace std;

int bt(int k, int n) {
    if (k <= n) return n - k;
    if (k % 2 == 0) return min(bt(k/2, n) + 1, k-n);
    return min(bt(k+1, n), bt(k-1, n)) + 1;
}

int main() {
    long long n, k;
    cin>>n>>k;
    if (n == 0) {
        cout << 1 + bt(k, 1) << '\n';
    } else {
        cout << bt(k, n) << '\n';
    }
    return 0;
}