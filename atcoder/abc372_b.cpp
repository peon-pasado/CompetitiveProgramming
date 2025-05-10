#include <bits/stdc++.h>
using namespace std;

vector<int> r;
void bt(int M) {
    if (M == 0) {
        cout<<r.size()<<'\n';
        reverse(r.begin(), r.end());
        for (auto v : r) cout << v << ' ';
        cout << '\n';
        exit(0);
        return;
    }
    int t = 1;
    int s = 0;
    while (3 * t <= M) {
        t *= 3;
        s++;
    }
    r.push_back(s);
    bt(M - t);
}

int main() {
    long long M;
    cin>>M;
    bt(M);
    return 0;
}