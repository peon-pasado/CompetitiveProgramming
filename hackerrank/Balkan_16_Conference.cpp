/**
 *  @author Miguel Mini
 *  @tag constructive
 *  @idea
 *    - we can obtain the position to the first
 *    journalist from right to left. we need 
 *    to maintain this for all people.
 *
 *    - the second part can be obtain update
 *    only meets with experiment days.
 *
**/


#include <bits/stdc++.h>
using namespace std;

struct Contact {
    int id;
    int time;
};

struct Meet {
    int a;
    int b;
};

const int inf = 1e9;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<Meet> meets(m);
    vector<int> date(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        meets[i] = {a, b};
    }
    for (int i = 1; i <= n; ++i) date[i] = inf;
    vector<Contact> contacts(n + 1);
    for (int i = 1; i <= k; ++i) {
        contacts[i] = {-1, -1};
    } 
    for (int i = k + 1; i <= n; ++i) {
        contacts[i] = {i, inf};
    }
    vector<int> firstContact(n + 1, -1);
    for (int i = m-1; i >= 0; --i) {
        if (contacts[meets[i].a].id == -1
           && contacts[meets[i].b].id == -1) {
            continue;
        }
        if (min(meets[i].a, meets[i].b) > k) {
            continue;
        }
        auto c1 = contacts[meets[i].a];
        auto c2 = contacts[meets[i].b];
        if (c1.id == -1 || c1.time < c2.time) {
            contacts[meets[i].a] = c2;
            if (meets[i].b > k) {
                contacts[meets[i].a].time = m - i - 1;
            }
        } else {
            contacts[meets[i].b] = c1;
            if (meets[i].a > k) {
                contacts[meets[i].b].time = m - i - 1;
            }
        }
        if (date[meets[i].a] == inf) {
            date[meets[i].a] = i;
            firstContact[meets[i].a] = 
                contacts[meets[i].a].id;
        } 
        if (date[meets[i].b] == inf) {
            date[meets[i].b] = i;
            firstContact[meets[i].b] = 
                contacts[meets[i].b].id;
        } 
    }
    vector<bool> learned(n + 1);
    for (int i = 0; i < m; ++i) {
        if (meets[i].a <= k 
            && date[meets[i].a] != inf 
            && date[meets[i].a] <= i) {
            learned[meets[i].a] = 1;
        }
        if (meets[i].b <= k 
            && date[meets[i].b] != inf 
            && date[meets[i].b] <= i) {
            learned[meets[i].b] = 1;
        }
        learned[meets[i].a] = 
            learned[meets[i].b] = 
                learned[meets[i].a] || learned[meets[i].b];
    }
    for (int i = 1; i <= k; ++i) {
        cout << (date[i]!=inf ? date[i]+1 : -1) << " \n"[i==k];
    }
    int sum = 0;
    for (int i = k + 1; i <= n; ++i) {
        sum += learned[i];
    }
    cout << sum;
    for (int i = k + 1; i <= n; ++i) {
        if (learned[i]) {
            cout << " " << i;
        }
    }
    cout << "\n";
    for (int i = 1; i <= k; ++i) {
        cout << firstContact[i] << " \n"[i==k];    
    }
    return 0;
}
