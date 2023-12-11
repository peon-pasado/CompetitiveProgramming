/**
 * @idea backtracking, math
 * 
 *  - the minimum number of swaps is the number 
 *  of inversions
 * 
 *  - simule swaps and map this:
 * 
 *      v0, v1, ..., vk
 * 
 *  with \sum_{i=0}^k vi x n^{k-i} 
*/

#include <bits/stdc++.h>
using namespace std;

int a[10];

set<int> s;
int bt(int pos, int n, int inver, int val) {
    if (inver == 0) return 0;
    if (pos == inver) {
        if (s.count(val)) return 0;
        s.insert(val);
        for (int i=1; i<n; ++i)
            if (a[i] < a[i-1]) return 0;
        return 1;
    }
    int ans = 0;
    for (int i=0; i+1<n; ++i) {
        swap(a[i], a[i+1]);
        ans += bt(pos+1, n, inver, val * 5 + i);
        swap(a[i], a[i+1]);
    }
    return ans;
}

int main() {
    int tc=1, n;
    while (cin>>n, n) {
        for (int i=0; i<n; ++i) {
            cin>>a[i];
        }
        int inver = 0;
        for (int i=1; i<n; ++i)
            for (int j=0; j<i; ++j)
                inver += a[i] < a[j];
        s.clear();
        cout << "There are " << bt(0, n, inver, 0) << " swap maps for input data set " << tc++ << ".\n";
    }
    return 0;
}