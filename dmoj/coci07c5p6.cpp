#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e4 + 1;
int res[maxn];
map<int, int> trie;
int cnt[580000];
short terminal[580000];
int el = 0;

void add(string& s, int id) {
    int root = 0;
    for (auto c : s) {
        cnt[root]++;
        int ch = c - 'a';
        if (!trie.count(ch | (root << 5))) {
            trie[ch | (root << 5)] = ++el;
        }
        root = trie[ch | (root << 5)];
    }
    terminal[root] = id;
    cnt[root]++;
}

int find(string& s) {
    int root = 0;
    for (auto c : s) {
        int ch = c - 'a';
        if (!trie.count(ch | (root << 5))) {
            return 0;
        }
        root = trie[ch | (root << 5)];
    }
    return terminal[root];
}

int calc(string& s) {
    int root = 0;
    int ans = 0;
    for (auto c : s) {
        ans += cnt[root];
        int ch = c - 'a';
        if (!trie.count(ch | (root << 5))) {
            return ans;
        }
        root = trie[ch | (root << 5)];
    }
    ans += cnt[root];
    return ans;
}

int main() {
    int n;
    string s;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> s;
        add(s, i);
        res[i] = calc(s);
    }   
    int q;
    cin >> q;
    while (q--) {
        cin >> s;
        int id = find(s);
        if (id > 0) cout << res[id] << '\n';
        else cout << calc(s) << '\n';
    }
    return 0;
}
