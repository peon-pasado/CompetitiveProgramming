#include <bits/stdc++.h>
#define sz(v) static_cast<int>(v.size())
#define clear_fit(v) v.clear(), v.shrink_to_fit()
#define all(v) v.begin(), v.end()
#define unique(v) v.erase(unique(all(v)), v.end())
#define fast_io cin.tie(nullptr)->sync_with_stdio(false)

template<typename T1, typename T2>
inline auto max(T1 a, T2 b) {return a > b ? a : b;}

template<typename T1, typename T2>
inline auto min(T1 a, T2 b) {return a < b ? a : b;}

using namespace std;

int st[19][250005];

struct reachability_tree {
    vector<vector<int>> g;
    vector<int> pi;
    vector<int> val;
    vector<int> ord;
    vector<pair<int, int>> range;
    int T;

    reachability_tree(int n) {
        g.resize(n);
        val.resize(n);
        pi.resize(n);
        ord.resize(n);
        iota(all(pi), 0);
    }

    int get(int x) {
        return x != pi[x] ? pi[x] = get(pi[x]) : x;
    }

    void merge(int x, int y, int time) {
        x = get(x);
        y = get(y);
        if (x == y) return;
        int new_node = g.size();
        g.resize(g.size() + 1);
        pi[x] = pi[y] = new_node;
        val.push_back(time);
        pi.push_back(new_node);
        g[new_node].push_back(x);
        g[new_node].push_back(y);
    }

    void build(vector<pair<pair<int, int>, int>> edges) {
        //sort(all(edges), [](auto p, auto q) {
        //    return p.first < p.second;
        //});
        for (auto e : edges) {
            merge(e.first.first, e.first.second, e.second);
        }
    }

    void dfs(int x, int p=-1) {
        st[0][x] = p==-1?x:p;
        for (int k=1; k<=18; ++k)
            st[k][x] = st[k-1][st[k-1][x]];
        if (g[x].empty()) {
            range[x] = {T, T};
            ord[x] = T++;
            return;
        }
        range[x] = {1e9, 0};
        for (auto v : g[x]) {
            dfs(v, x);
            range[x].first = min(range[x].first, range[v].first);
            range[x].second = max(range[x].second, range[v].second);
        } 
    }

    void make_tree() {
        T = 0;  
        range.resize(g.size());
        for (int i = 0; i < g.size(); ++i) {
            if (pi[i] == i) {
                dfs(i);
            }
        }
    }

    pair<int, int> get_range(int x, int t) {
        for (int k=18; k>=0; --k) {
            if (val[st[k][x]] <= t) {
                x = st[k][x];
            }
        }
        return range[x];
    }

};

const int inf = 1e9;
struct range_set {

    set<pair<pair<int, int>, int>> s;

    range_set() {}

    int intersect(pair<int, int> p, pair<int, int> q) {
        return min(p.second, q.second) - max(p.first, q.first) + 1;
    }

    int add(int l, int r, int x, int delta) {
        auto q = s.lower_bound({{l, r}, -inf});
        if (q != s.begin()) q = prev(q);
        int sum = 0;
        if (q != s.end()) {
            //cout << "here" << endl;
            auto L = q;
            if (intersect(L->first, {l, r}) <= 0) L = next(L);
            auto R = L;
            while (R != s.end() && intersect(R->first, {l, r}) > 0) R = next(R);
            vector<pair<pair<int, int>, int>> to_add;
            for (auto it = L; it != R; ++it) {
                //cout << "iteration" << endl;
                int tot = intersect(it->first, {l, r});
                if (x - delta >= it->second) sum += tot;
                if (it->first.first < l) to_add.push_back({{it->first.first, l - 1}, it->second});
                if (r < it->first.second) to_add.push_back({{r + 1, it->first.second}, it->second});
            }
            s.erase(L, R);
            for (auto r : to_add) s.insert(r);
        }
        s.insert({{l, r}, x});
        return sum;
    }   
};

const int maxn = 1e5 + 10;
int t, n, q, x;

int main() {
    cin>>t;
    while (t--) {
        cin>>n;
        vector<pair<int, pair<int, int>>> edges;
        for (int i=0; i<n-1; ++i) {
            int u, v, l;
            cin>>u>>v>>l;
            edges.push_back({l, {u, v}});
        }   
        sort(all(edges));
        reachability_tree dsu(n + 1);
        for (auto [w, e] : edges) {
            dsu.merge(e.first, e.second, w);
        }
        dsu.make_tree();
        cin>>q>>x;
        range_set s;
        s.add(1, n, -x, x);
        while (q--) {
            int d, u, k;
            cin>>d>>u>>k;
            auto r = dsu.get_range(u, k);
            //cout << "range: " << r.first << " " << r.second << endl;
            cout << s.add(r.first, r.second, d, x) << '\n';
        }
    }
    return 0;
}