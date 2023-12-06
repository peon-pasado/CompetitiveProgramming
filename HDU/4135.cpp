/**
 * @idea backtracking, PIE
 * 
 * - use inclusin-exclusion-principle over primes of N.
 * The sets are A_i = {n | a <= n <= b s.t. n = 0 (mod p_i)} 
 * 
 * - use backtracking for enumerate the sets.
**/
#include <iostream>
#include <vector>
using namespace std;

vector<int> p;
long long a, b;
long long bt(int mul, int pos, int t) {
    if (pos == (int)p.size()) {
        if (t & 1) return - (b / mul - ((a - 1) / mul));
        return b / mul - (a - 1) / mul;
    }
    return bt(mul, pos + 1, t) + bt(mul * p[pos], pos + 1, t + 1);
}

int main() {
    int t;
    cin>>t;
	for (int tc=1; tc<=t; ++tc) {
        int n;
        cin>>a>>b>>n;
        p.clear();
        for (int i=2; i*i<=n; ++i) {
            if (n % i == 0) {
                while (n % i == 0) n /= i;
                p.push_back(i);
            }
        }
        if (n > 1) p.push_back(n);
        cout << "Case #" << tc << ": "; 
        cout << bt(1, 0, 0) << '\n';
    }
    return 0;
}