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

struct dsu_rollback {

    vector<int> pi;
    vector<size_t> size_tree;
    stack<int> changes;

    dsu_rollback() {}
    
    dsu_rollback(int n) {
        pi.resize(n);
        iota(all(pi), 0);
        size_tree.resize(n, 1);
    }

    void add() {
        pi.push_back(sz(pi));
        size_tree.push_back(1);
    }

    int get_root(int x) {
        return pi[x] != x ? get_root(pi[x]) : x;
    }

    void merge(int u, int v) {
        u = get_root(u);
        v = get_root(v);

        if (u == v) {
            changes.push(-1);
            return;
        }
        if (size_tree[u] < size_tree[v]) swap(u, v);
        
        size_tree[u] += size_tree[v];
        pi[v] = u;
        changes.push(v);
    } 

    bool same(int u, int v) {
        return get_root(u) == get_root(v);
    }

    void undo() {
        if (changes.empty()) return;
        if (changes.top() >= 0) {
            int v = changes.top();
            size_tree[pi[v]] -= size_tree[v];
            pi[v] = v;          
        }
        changes.pop();
    }
};

const int maxn = 2e5 + 10;
map<int, int> id[maxn * 2];
pair<int, int> qu[maxn];
vector<int> events[maxn * 2];
int state[maxn * 2];
vector<pair<int, int>> st[maxn * 4];
int ptr[maxn * 2];
bool is_query[maxn];
int n, m;

dsu_rollback dsu;
int last_ans = 0;

void update(int x, int l, int r, int ll, int rr, pair<int, int> p) {
    if (r < ll || rr < l) return;
    if (ll <= l && r <= rr) {
        st[x].push_back(p);
        return;
    }
    int mid = (l+r)/2;
    update(2*x, l, mid, ll, rr, p);
    update(2*x+1, mid+1, r, ll, rr, p);
}

void solve(int nx, int l, int r) {
    int time = sz(dsu.changes);
    for (auto e : st[nx])
        dsu.merge(e.first, e.second);
    
    if (l == r) {
        int x = (qu[r].first + last_ans - 1) % n + 1;
        int y = (qu[r].second + last_ans - 1) % n + 1; 
        if (is_query[r]) {
            cout << (last_ans = dsu.same(x, y));
        } else {
            if (x > y) swap(x, y);
            state[id[x][y]] ^= 1;
            for (int i=0; i<2; ++i) {
                int x = (qu[r].first + i - 1) % n + 1;
                int y = (qu[r].second + i - 1) % n + 1; 
                if (x > y) swap(x, y);
                int j = id[x][y];
                ptr[j]++;
                if (state[j]) update(1, 0, m-1, l+1, events[j][ptr[j]], {x, y});
            }
        }
    } else {
        int mid = (l+r)/2;
        solve(2*nx, l, mid);
        solve(2*nx+1, mid+1, r);
    }
    while (sz(dsu.changes) > time) dsu.undo();
}

int main() {
    fast_io;
    cin>>n>>m;
    dsu = dsu_rollback(n + 1);
    int ti = 0;
    for (int i=0; i<m; ++i) {
        int t, x, y;
        cin>>t>>x>>y;
        is_query[i] = t == 2;
        qu[i] = {x, y};
        if (t==1) {
            for (int j=0; j<2; ++j) {
                int a = (x+j-1) % n + 1;
                int b = (y+j-1) % n + 1; 
                if (a > b) swap(a, b);
                if (!id[a].count(b)) id[a][b] = ti++;
                events[id[a][b]].push_back(i);
            }
        }
    }
    for (int i=0; i<ti; ++i) {
        events[i].push_back(m);
    }
    solve(1, 0, m-1);
    cout << '\n';
    return 0;
}