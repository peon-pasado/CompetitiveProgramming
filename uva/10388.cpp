#include <bits/stdc++.h>
using namespace std;

char card[2][2][102];
int n[2][2];

bool empty(bool is_john) {
    return n[0][is_john] == 0;
}

bool is_win(bool is_john) {
    return n[0][!is_john] == 0 && n[1][!is_john] == 0;
}

void rebase_cards(bool is_john) {
    while (n[1][is_john] > 0) {
        card[0][is_john][n[0][is_john]++] = card[1][is_john][--n[1][is_john]];
    }
}

void move_snap(bool is_john) {
    if (empty(is_john)) {
        rebase_cards(is_john);
    }
    card[1][is_john][n[1][is_john]++] = card[0][is_john][--n[0][is_john]];
}

bool snap() {
    return card[1][0][n[1][0] - 1] == card[1][1][n[1][1] - 1];
}

void stole(bool is_john) {
    for (int i = 0; i < n[1][!is_john]; ++i) {
        card[1][is_john][n[1][is_john]++] = card[1][!is_john][i];
    }
    n[1][!is_john] = 0;
}

bool snap_first() {
    return rand() / 141 % 2;    
}

string name[2] = {"Jane", "John"};

void print(bool is_john) {
    for (int i = n[1][is_john]-1; i>=0; --i) {
        cout << card[1][is_john][i];
    }
}

int main() {
    //srand(time(nullptr));
    int t;
    cin>>t;
    while (t--) {
        string A, O;
        cin>>A>>O;
        for (int i=0; i<2; ++i)
            for (int j=0; j<2; ++j)
                n[i][j] = 0;
        reverse(A.begin(), A.end());
        for (auto c : A) card[0][0][n[0][0]++] = c;
        reverse(O.begin(), O.end());
        for (auto c : O) card[0][1][n[0][1]++] = c;
        bool win = false;
        for (int i = 0; i < 1000; ++i) {
            move_snap(0); move_snap(1);
            if (snap()) {
                bool who = snap_first();
                stole(who);
                cout << "Snap! for " << name[who] << ": ";
                print(who);
                cout << '\n';
                if (is_win(who)) {
                    win=true;
                    cout << name[who] << " wins." << '\n';
                    break;
                }
            }
        }
        if (!win) cout << "Keeps going and going ..." << '\n';
        if (t) cout << '\n';
    }
    return 0;
}