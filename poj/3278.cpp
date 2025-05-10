#include <iostream>
#include <cstring>
#include <queue>
#include <bitset>
using namespace std;

//+1 y -1 no se hacen a la misma vez
//intercambia un x2 siempre, a menos que sea mejor no usarlo.
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