/**
 * @idea meet-in-the-middle, backtracking, bitmask
 * 
 *  - we can divide the problem in two halves, and
 *  generate partial sum of the big set and partial
 *  sum of the subset with sum == sum set / 2. 
 * 
 *  - that sums are A, a and B, b in the other group.
 *  we can calculate A - 2a and -B + 2b, and compare
 *  these for equal. 
 * 
 *  - we can enumerate every sum A - 2a for A. in O(sqrt(3)^n)
 *  and for -B + 2b.
 * 
 *  - for every of that we can make a bitset with every set
 *  in a group with the same value.
 * 
 *  - and in the other group we intersect every bitset with a
 *  same value. en O(sqrt(2)^n / 32))
 *   
 * - final complexity: O(sqrt(6)^n / 32)
**/
#include <bits/stdc++.h>
using namespace std;

const int N = 20;
int w[N];
int n;
vector<int> P[2][1<<10];
void bt(int l, int r, int sum, int mask, int id) {
    if (l == r) return void(P[id][mask].push_back(sum)); 
    bt(l+1, r, sum, 2 * mask, id);    
    bt(l+1, r, sum+w[l], 2 * mask + 1, id);
    bt(l+1, r, sum-w[l], 2 * mask + 1, id);    
}

bitset<1024> masks[59050 * 2 + 1], var;

// a + b = 2 * (c + d)
// a - 2*c = 2*d - b

int main() {
    cin>>n;
    for (int i=0; i<n; ++i) cin>>w[i];
    bt(0, n/2, 0, 0, 0);
    bt(n/2, n, 0, 0, 1);
    int m[] = {1<<n/2, 1<<(n+1)/2};
    vector<int> id;
    for (int i=0; i<2; ++i)
        for (int j=0; j<m[i]; ++j)
            for (int v : P[i][j])
                id.push_back(i == 0 ? v : -v);
    sort(id.begin(), id.end());
    id.erase(unique(id.begin(), id.end()), id.end());
    for (int i=0; i<2; ++i)
        for (int j=0; j<m[i]; ++j)
            for (int& v : P[i][j])
                v = lower_bound(id.begin(), id.end(), i == 0 ? v : -v) - id.begin();

    for (int j=0; j<m[0]; ++j)
        for (int v : P[0][j])
            masks[v][j] = 1;

    long long ans = 0;
    for (int j=0; j<m[1]; ++j) {
        var.reset();
        for (int v : P[1][j]) {
            var |= masks[v];
        }
        ans += var.count();
    }

    cout << ans - 1 << '\n';
    return 0;
}