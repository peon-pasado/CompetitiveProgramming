#include <bits/stdc++.h>
#define double long double
using namespace std;

const int maxn = 10;
double x[maxn];
double bt(int pos, vector<int>& r) {
    if (pos == r.size()) {
        return x[(int)r.size() - 1];
    }
    x[pos] = 0.;
    for (int i=0; i<pos; ++i) {
        x[pos] = max(x[pos], x[i] + 2 * sqrt(r[i] *1ll* r[pos]));
    }
    return bt(pos+1, r);
}


int main() {
    cout<<fixed;
    cout.precision(14);
    int n;
    cin>>n;
    vector<int> r(n);
    for (int i=0; i<n; ++i) {
        cin>>r[i];
    }
    sort(r.begin(), r.end());
    double mind = 1e18;
    while (1) {
        mind = min(mind, bt(1, r));
        if (!next_permutation(r.begin(), r.end())) {
            break;
        }
    }
    cout<<mind<<'\n';
    return 0;
}