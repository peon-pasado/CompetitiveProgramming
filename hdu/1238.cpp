#include <bits/stdc++.h>
#define rep(i, n) for (int i=0; i<n; ++i)
#define trav(e, v) for (auto e : v)
#define all(v) v.begin(), v.end()
#define sz(v) ((int)v.size())
using namespace std;

using vi=vector<int>;
const int maxn = 1000 + 10;
const int sigma = 62;
using ll = long long;

void format(string& s) {
    for (auto& ch : s) {
        if (ch <= 'Z') ch = ch - 'A'; //change
        else ch = ch - 'a' + 26;
    }
}

struct AC {
    vector<vi> nxt, go;
    vector<string> S;
    vector<ll> H;
    vector<vector<int>> leaf;//change
    vector<pair<int, int>> rev;
    vector<ll> value;
    vi lnk;
    AC() {}
    int size() {
        return S.size();
    }
    void add_str(string& v, ll h) {
        format(v);
        S.emplace_back(move(v));
        H.emplace_back(h);
    }
    void build() {
        make_trie();
        make_automaton();
    }
    size_t add_tr() {
        nxt.emplace_back(vi(sigma));
        //leaf.emplace_back(vector<>);//change
        return sz(nxt) - 1;
    }
    void add_trie(const string& s, ll h) {
        size_t r=0;
        for (const auto& c : s) {
            if (!nxt[r][c]) nxt[r][c]=add_tr();
            r = nxt[r][c];
        }
        if (rev.empty() || rev.back().second != -1) {
            rev.push_back({r, -1});
        } else {
            rev.back().second = r;
        }
        //leaf[r].push_back(h);
    }
    void make_trie() {
        add_tr();
        rep(i, sz(S)) {
            add_trie(S[i], H[i]);
        }
    }
    void make_automaton() {
        go.assign(sz(nxt), vi(sigma, 0));
        lnk.assign(sz(nxt), 0);
        //value.assign(sz(nxt), 0);
        queue<int> Q;
        Q.push(0);
        while (!Q.empty()) {
            int q = Q.front(); Q.pop();
            //value[q] = leaf[q] + value[lnk[q]]; //change
            rep(i, sigma) {
                if (nxt[q][i]) {
                    lnk[go[q][i]=nxt[q][i]] = (q>0)*go[lnk[q]][i];
                    Q.emplace(nxt[q][i]); 
                } else {
                    go[q][i] = (q>0)*go[lnk[q]][i];
                }
            }
        }
    }
    void merge_dsu(AC& other) {
        rep(i, sz(other.S)) {
            add_trie(other.S[i], other.H[i]);
            this->S.emplace_back(other.S[i]);
            this->H.emplace_back(other.H[i]);
        }
        //make_automaton();
    }
    friend AC merge(const AC& L, const AC& R) {
        AC M;
        M.S.insert(M.S.end(), all(L.S));
        M.S.insert(M.S.end(), all(R.S));
        M.H.insert(M.H.end(), all(L.H));
        M.H.insert(M.H.end(), all(R.H));
        M.build();
        return move(M);
    }
};

int main() {
    int t;
    cin>>t;
    while (t--) {
        int n;
        cin>>n;
        string u;
        vector<string> s(n);
        rep(i, n) {
            cin>>s[i];
            if (u.empty() || sz(u) > sz(s[i]))
                u = s[i];        
        }
        rep(i, n) format(s[i]);
        auto f = [&](int m) {
            AC T; 
            for (int i = 0; i + m - 1 < sz(u); ++i) {
                string s = u.substr(i, m);
                string rs = s;
                reverse(all(rs));
                T.add_str(s, i);
                T.add_str(rs, i);
            }
            T.build();
            vector<bool> d(sz(T.nxt));
            vector<int> cnt(sz(u) - m + 1);
            for (int i = 0; i < n; ++i) {
                int r = 0;
                for (auto c : s[i]) {
                    d[r = T.go[r][c]] = true;
                }
                for (int j = 0; j + m - 1 < sz(u); ++j) {
                    int a = T.rev[j].first, b = T.rev[j].second;
                    if (d[a] || d[b]) cnt[j]++;
                }
                r = 0;
                for (auto c : s[i]) {
                    d[r = T.go[r][c]] = false;
                }
            }
            for (int i = 0; i < sz(u) - m + 1; ++i)
                if (cnt[i] == n) 
                    return true;
            return false;
        };
        int lo = 0, hi = sz(u) - 1;
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (f(mid)) lo = mid;
            else hi = mid-1;
        }
        cout << lo << endl;
    }
    return 0;
}