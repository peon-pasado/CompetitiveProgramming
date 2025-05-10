#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin>>n;
    bool y = 1;
    int z = -1;
    for (int i=0; i<n; ++i) {
        int x;
        cin>>x;
        if (i > 0 && x != z) y = 0;
        z = x;
    } 
    cout << (y ? "Yes" : "No") << '\n';
    return 0;
}