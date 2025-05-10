#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
const ll mod = 1e18 + 3;
ll B = 1e5 + rand() % 100000;

vector<ll> pot = {1};

ll add(ll a, ll b) {
    return a+b<mod?a+b:a+b-mod;
}

ll mul(ull a, ull b, ull M=mod) {
	ll ret = a * b - M * ull(ld(a) * ld(b) / ld(M));
	return ull(ret + M * (ret < 0) - M * (ret >= (ll)M));
}

ll get_pot(int i) {
    while (pot.size() <= i) {
        pot.push_back(mul(pot.back(), B));
    }
    return pot[i];
}

struct MyHash {
    ll v;

    MyHash(ll x) {v = x;}

    MyHash(char c) {v = c;}

    bool operator<(MyHash h) const {
        return v < h.v;
    }

    MyHash operator+(MyHash x) {
        return MyHash(add(v, x.v));
    }

    MyHash operator-(MyHash x) {
        return MyHash(add(v, mod - x.v));
    }

    bool operator==(MyHash x) {
        return v == x.v;
    }

    MyHash shift(int d) {
        return mul(v, get_pot(d));
    }

};

template<class MyHash>
struct StringHash {
    vector<MyHash> hash;

    size_t size() {
        return hash.size();
    }

    MyHash get_hash(int l, int r) {
        if (l == 0) return hash[r];
        return hash[r] - hash[l-1].shift(r-l+1);
    }

    void append(char c) {
        if (hash.empty()) hash.push_back(MyHash(c));
        else hash.push_back(hash.back().shift(1) + MyHash(c));
    }
};

int main() {
    int n, k;
    string s1, s;
    cin >> n >> k;
    cin >> s1;
    StringHash<MyHash> h;
    for (auto c : s1) h.append(c);
    for (int i = 0; i < k; ++i) h.append(s1[i]);
    int g;
    cin >> g;
    map<MyHash, int> ss;
    for (int i = 0; i < g; ++i) {
        cin >> s;
        MyHash hs(s[0]);
        for (int j = 1; j < s.size(); ++j) {
            hs = hs.shift(1) + MyHash(s[j]);
        }
        ss[hs] = i + 1;
    }
    for (int i = 0; i < k; ++i) {
        set<MyHash> s2;
        for (int j = 0; j < n; ++j) {
            s2.insert(h.get_hash(j*k+i, (j+1)*k+i-1));
        }
        if (s2.size() == n) {
            bool ok = 1;
            for (auto e : s2) {
                if (!ss.count(e)) {
                    ok = 0;
                    break;
                }
            }           
            if (ok) {
                cout << "YES" << '\n';
                for (int j = 0; j < n; ++j) {
                    cout << ss[h.get_hash(j*k+i, (j+1)*k+i-1)] << ' ';
                }
                cout << endl;
                exit(0);
            }
        }
    }
    cout << "NO" << endl;
    return 0;
}