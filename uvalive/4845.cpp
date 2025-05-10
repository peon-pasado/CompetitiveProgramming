#include <bits/stdc++.h>
using namespace std;

char T[2][10][10];
set<char> S[2][5], U[5];

int ns = 0, k;
string r = "00000";
void bt(int pos) {
    if (k == 0) return;
    if (pos == 5) {
        k--;
        if (k == 0) cout << r << '\n';
        return;
    }
    for (auto c : U[pos]) {
        r[pos] = c;
        bt(pos+1);
    }
}

int main() {
    int t;
    cin>>t;
    while (t--) {
        cin>>k;
        for (int i = 0; i < 5; ++i) {
            S[0][i].clear(); S[1][i].clear();
            U[i].clear();
        }
        for (int d=0; d<2; ++d) {
            for (int i=0; i<6; ++i) {
                for (int j=0; j<5; ++j) {
                    //cin>>T[d][i][j];
                    char x;
                    cin>>x;
                    //cout << x;
                    S[d][j].insert(x);
                }
                //cout << endl;
            }
            //cout << endl;
        }
        for (int j = 0; j < 5; ++j) {
            for (int i = 'A'; i <= 'Z'; ++i) {
                if (S[0][j].count(i) && S[1][j].count(i)) {
                    U[j].insert(i);
                }
            }
        }
        bt(0);
        if (k > 0) cout << "NO\n";
    }
    return 0;
}