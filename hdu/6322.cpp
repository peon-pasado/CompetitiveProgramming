#include <iostream>
using namespace std;

int main() {
    int t;
    cin>>t;
    while (t--) {
        int n;
        cin>>n;
        if (n == 1) cout << 5 << '\n';
        else if (n == 2) cout << 7 << '\n';
        else cout << n + 5 << endl;
    }
    return 0;
}