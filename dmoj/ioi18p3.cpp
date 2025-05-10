#include "werewolf.h"
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

int st[19][400005];

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


void calc(vector<pair<int, pair<int, int>>>& edges, int n, vector<pair<int, int>>& queries, vector<int>& p, vector<pair<int, int>>& r) {
    reachability_tree dsu(n);
    for (auto e : edges) {
        dsu.merge(e.second.first, e.second.second, e.first);
    }
    dsu.make_tree();
    for (int i=0; i<n; ++i) p[i] = dsu.ord[i];
    for (int i=0; i<sz(queries); ++i) r[i] = dsu.get_range(queries[i].first, queries[i].second);
}

const int maxn = 2e5 + 10;
int ft[maxn];

void add(int x) {
    while (x < maxn) {
        ft[x]++;
        x |= (x+1);
    }       
}

int query(int x) {
    int ans = 0;
    while (x >= 0) {
        ans += ft[x];
        x = (x & (x + 1)) - 1;
    }   
    return ans;
} 


std::vector<int> check_validity(int N, std::vector<int> X, std::vector<int> Y, std::vector<int> S, std::vector<int> E, std::vector<int> L, std::vector<int> R) {
    memset(ft, 0, sizeof ft);                                                                                    
    int M = X.size();
    int Q = S.size();
    vector<pair<int, pair<int, int>>> edges(M);
    for (int i=0; i<M; ++i) {
        edges[i] = {N - min(X[i], Y[i]), {X[i], Y[i]}};
    }
    sort(all(edges));
    vector<int> px(N), py(N);
    vector<pair<int, int>> rx(Q), ry(Q);
    vector<pair<int, int>> qx(Q), qy(Q);
    for (int i=0; i<Q; ++i) {
        qx[i] = {S[i], N - L[i]};
        qy[i] = {E[i], R[i]};
    }
    calc(edges, N, qx, px, rx);
    for (int i=0; i<M; ++i) {
        edges[i] = {max(X[i], Y[i]), {X[i], Y[i]}};
    }
    sort(all(edges));
    calc(edges, N, qy, py, ry);
    vector<pair<pair<int, int>, int>> s;
    for (int i=0; i<N; ++i)
        s.push_back({{px[i]+1, py[i]+1}, 0});
    for (int i=0; i<Q; ++i) {
        s.push_back({{rx[i].second+1, ry[i].second+1}, (i + 1)});
        s.push_back({{rx[i].first, ry[i].first}, (i + 1)});
        s.push_back({{rx[i].first, ry[i].second+1}, -(i+1)});
        s.push_back({{rx[i].second+1, ry[i].first}, -(i+1)});     
    }
    sort(all(s), [](auto p, auto q) {
        return p.first < q.first || (p.first == q.first && abs(p.second) < abs(q.second));
    });
    vector<int> qq(Q);
    for (auto e : s) {
        if (e.second == 0) {
            add(e.first.second);        
        } else {
            int sign = e.second > 0 ? 1 : -1;
            qq[abs(e.second)-1] += sign * query(e.first.second);
        }
    }
    for (int i=0; i<Q; ++i) qq[i] = qq[i] > 0;
    return qq; 
}

/**

int main() {
    int N, M, Q;
    cin>>N>>M>>Q;
    vector<int> X(M), Y(M), S(Q), E(Q), L(Q), R(Q);
    for (int i=0; i<M; ++i) {
        cin>>X[i]>>Y[i];
    }
    for (int i=0; i<Q; ++i) {
        cin>>S[i]>>E[i]>>L[i]>>R[i];
    }
    auto A = check_validity(N, X, Y, S, E, L, R);
    for (auto x : A) cout << x << ' ';
    cout << '\n';
    return 0;
}

**/