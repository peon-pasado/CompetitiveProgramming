#include <bits/stdc++.h>
using namespace std;

const int maxn = ((50050)>>6)<<6;
bool is_root[maxn];
int lo[maxn], hi[maxn];
int in_cycle[maxn];
int vis[maxn];
int down[maxn];
int semiroot[maxn];
int n, m, q;
int p[maxn];
vector<int> cycl_no[maxn];
vector<int> g[maxn];
int dis[maxn];

template<int N>
struct persistent_bset {

    struct Node {
        Node* l;
        Node* r;
        unsigned long long value;
    } *root;

    friend void build(Node* ro, int f, int pl = 0, int pr = (N>>6) - 1) {
        if (pl == pr) {
            ro->value = (uint64_t)-f; //0 -> 0000 | 1 -> 1111
            return;
        }
        int mid = (pl + pr) / 2;
        ro->l = new Node();
        ro->r = new Node();
        build(ro->l, f, pl, mid);
        build(ro->r, f, mid+1, pr);
    }

    friend Node* make_cpy(Node* x) {
        Node* c = new Node();
        c->l = x->l;
        c->r = x->r;
        c->value = x->value;
        return c; 
    }

    Node* update_set(int x) {
        Node* nroot = make_cpy(root);
        update(root, nroot, x);
        return nroot;
    }

    friend void update(Node* p, Node* q, int ps, int bl=0, int br=(N>>6)-1) {
        if (bl == br) {
            q->value ^= (1ull<<ps);
            assert(ps >= 0 && ps < 64);
            return;
        }
        int mi = (bl + br) / 2;
        if (ps < ((mi - bl + 1)<<6)) {
            q->l = make_cpy(p->l);
            update(p->l, q->l, ps, bl, mi);
        } else {
            q->r = make_cpy(p->r);
            update(p->r, q->r, ps - ((mi - bl + 1)<<6), mi+1, br);
        }
    }

    friend void update_inplace(Node* p, Node* q) {
        if (p->l == nullptr) {
            p->value ^= q->value;
            return;
        }
        update_inplace(p->l, q->l);
        update_inplace(p->r, q->r);
    }

    friend int count(Node* p, int l1, int r1, int l=0, int r=N-1) {
        int bl = l>>6, br = r>>6;
        if (bl == br) {
            //bl * 64, bl * 64 + 63
            int sl = l & 63, sr = (l & 63) + 63;
            int ul = l1 - (bl << 6), ur = r1 - (bl << 6);
            ul = max(sl, ul); 
            ur = min(sr, ur);
            if (ul <= ur) {
                uint64_t t = (((1ull<<(ur - ul)) - 1)<<1)|1; 
                return __builtin_popcountll((t << ul) & p->value);
            }
            return 0;
        }
        int mi = (bl + br) / 2;
        return count(p->l, l1, r1, l, (mi<<6) + 63) + count(p->r, l1, r1, (mi+1)<<6, r);
    }


    persistent_bset() {
       root = new Node();
       root->l = root->r = nullptr;
    }
};

persistent_bset<maxn> sp[maxn], lp[maxn];

vector<int> order;
void bfs(int s) {
    queue<int> Q;
    Q.push(s);
    vis[s] = 1;
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        order.emplace_back(u);
        for (int v : g[u]) {
            if (v == p[u]) continue;            
            if (!vis[v]) {
                vis[v] = 1;
                p[v] = u;
                dis[v] = dis[u] + 1;
                Q.push(v);
            } else if (dis[v] == dis[u]) {
                int x = u, y = v; 
                in_cycle[u] = in_cycle[v] = 1;
                vector<int> nos = {u, v};
                while (p[x] != p[y]) {
                    down[p[x]] = x; down[p[y]] = y;
                    in_cycle[p[x]] = in_cycle[p[y]] = 1;
                    x = p[x]; y = p[y];
                    nos.emplace_back(x);
                    nos.emplace_back(y);
                }
                semiroot[x] = semiroot[y] = 1;
                is_root[p[x]] = 1;
                cycl_no[x] = cycl_no[y] = nos;
            }
        }
    }
}

int T;
void dfs(int x) {
    lo[x] = T++;
    vis[x] = 1;
    for (int v : g[x]) {
        if (vis[v]) continue;
        if (dis[x] == dis[v]) continue;
        dfs(v);
    }
    hi[x] = T-1;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin>>n>>m>>q;
    for (int i=0; i<m; ++i) {
        int u, v;
        cin>>u>>v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    bfs(1);
    memset(vis, 0, sizeof vis);
    dfs(1);
    persistent_bset<maxn> r;
    build(r.root, 1);
    for (auto u : order) {
        if (u == 1) {
            build(sp[u].root, 0);
            sp[u].root = sp[u].update_set(lo[u]);

            build(lp[u].root, 0);
            lp[u].root = lp[u].update_set(lo[u]);
        } else {
            sp[u].root = sp[p[u]].update_set(lo[u]);
            if (!in_cycle[u]) {
                lp[u].root = lp[p[u]].update_set(lo[u]);
            } else if (semiroot[u]) {
                lp[u].root = lp[p[u]].update_set(lo[cycl_no[u][0]]);
                for (int i=1; i < (int)cycl_no[u].size(); ++i) {
                    lp[u].root = lp[u].update_set(lo[cycl_no[u][i]]);
                }
            } else {
                lp[u].root = lp[p[u]].update_set(lo[p[u]]);
            }
        }
    }
    while (q--) {
        int op, x;
        cin>>op>>x;
        if (op == 1) update_inplace(r.root, sp[x].root);
        else if (op == 2) update_inplace(r.root, lp[x].root);
        else {
            int ans = count(r.root, lo[x], hi[x]);
            int a = down[x];
            if (a != 0 && lo[x] <= lo[a] && hi[a] <= hi[x]) {
                ans -= count(r.root, lo[a], hi[a]);
            } 
            cout << ans << '\n';
        }
    }
    return 0;
}