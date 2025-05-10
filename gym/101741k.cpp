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

const int maxn = 1e5 + 10;
set<pair<MyHash, int>> sh[maxn];
int last[maxn];
int res[maxn];

int main() {
    int n, m;
    string s;
    cin >> n >> m;
    cin >> s;
    StringHash<MyHash> h;
    for (auto c : s) h.append(c);
    string sq;
    vector<int> sizes;
    for (int i = 0; i < m; ++i) {
        cin >> sq;
        MyHash hq(sq[0]);
        for (int i = 1; i < sq.size(); ++i) {
            hq = hq.shift(1) + MyHash(sq[i]);
        }
        sh[sq.size()].insert({hq, i});
        sizes.push_back(sq.size());
    }
    memset(last, -1, sizeof last);
    sort(sizes.begin(), sizes.end());
    sizes.erase(unique(sizes.begin(), sizes.end()), sizes.end());
    for (int i = 0; i < s.size(); ++i) {
        for (int len : sizes) {
            if (i-len+1<0) break;
            auto hh = h.get_hash(i-len+1, i);
            auto qu = sh[len].lower_bound({hh, -1});
            if (qu != sh[len].end() && hh == qu->first) {
                int id = qu->second;
                if (last[id] < i-len+1) {
                    last[id] = i;
                    res[id] += 1;
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        pair<MyHash, int> last_h = make_pair(MyHash(-1ll), -1);
        for (auto v : sh[i]) {
            if (v.first == last_h.first) res[v.second] = res[last_h.second];
            last_h = v;
        }
    }
    for (int i = 0; i < m; ++i) {
        cout << res[i] << '\n';
    }
    return 0;
}