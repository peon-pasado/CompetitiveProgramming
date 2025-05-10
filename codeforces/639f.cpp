#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int maxn = 3e5 + 10;
int comp_id[maxn], id;
vi num;
int N;
vector<vector<pii>> ed(maxn);
bool bridge[2*maxn];
int Time;

int dfs(vector<vector<pii>> &ed, bool bridge[], int at, int par, bool ok=0) {
    if (ok) comp_id[at] = id;
    int me = num[at] = ++Time, e, y, top = me;
    trav(pa, ed[at]) if (pa.second != par) {
        tie(y, e) = pa;
        if (num[y])
            top = min(top, num[y]);
        else {
            int up = dfs(ed, bridge, y, e, ok);
            top = min(top, up);
            if (up > me) bridge[e] = 1;
        }
    }
    return top;
}

void bicomps() {
    num.assign(N, 0);
    rep(i, 0, N) if (!num[i]) {
        dfs(ed, bridge, i, -1, 1);
        id++;
    }
}

vi bT[maxn];
void add_edge(vi T[], int a, int b) {
    T[a].push_back(b);
    T[b].push_back(a);
}

int color[maxn];
void init(int n) {
    rep(i, 0, n) color[i] = -1;
    rep(i, 0, n) bT[i].clear();
}

void make_tree(int x, int r) {
    color[x] = r;
    for (auto [u, i] : ed[x])
        if (bridge[i]) {
            if (~color[u]) 
                add_edge(bT, r, color[u]);
        } else if (color[u]==-1)
            make_tree(u, r);   
}

int st[maxn][19];
int h[maxn];
int lo[maxn], hi[maxn];
int C;
void dfs_lca(int x, int p=-1) {
    lo[x]=C++;
    h[x]=p==-1?0:h[p]+1;
    st[x][0]=p==-1?x:p;
    rep(i, 1, 19)
        st[x][i] = st[st[x][i-1]][i-1];
    trav(v, bT[x]) {
        if (v==p) continue;
        dfs_lca(v, x);
    }
    hi[x]=C++;
}

int lca(int x, int y) {
    if (h[x]>h[y])
        swap(x, y);
    for (int i=18; i>=0; --i)
        if (h[st[y][i]]>=h[x])
            y=st[y][i];
    if (x==y) 
        return x;
    for (int i=18; i>=0; --i)
        if (st[x][i]!=st[y][i]) {
            x=st[x][i];
            y=st[y][i];
        }
    return st[x][0];
}

vector<vector<pii>> aux(maxn);
int eid;
bool vis[maxn];
int auxiliary_tree(vector<int> cl) {
    auto cmp = [&](int u, int v) { 
        return lo[u] < lo[v]; 
    }; 
    sort(all(cl), cmp);
    int n = sz(cl);
    rep(i, 1, n) cl.push_back(lca(cl[i-1], cl[i]));
    sort(all(cl), cmp);
    cl.erase(unique(all(cl)), cl.end());
    trav(v, cl) {
        //cout << v << " ";
        aux[v].clear();
        vis[v] = num[v] = 0;
    }
    //cout << endl;
    stack<int> s({cl[0]});
    int root = cl[0];
    rep(i, 1, sz(cl)) {
        while (!s.empty() && hi[s.top()] < lo[cl[i]])
            s.pop();
        aux[s.top()].emplace_back(cl[i], eid);
        aux[cl[i]].emplace_back(s.top(), eid++);
        s.push(cl[i]);
    }
    return root;
}

int R;
int rotate(int element) {
    element = (element + R) % N;
    if (element == 0) {
        element = N;
    }
    return element;
}

bool need[maxn];
int dfs_cnt(int x) {
    //cout << x << " " << "dfs" << endl;
    vis[x] = 1;
    int ans = need[x];
    for (auto [u, i] : aux[x]) {
        if (bridge[i]) continue;
        if (vis[u]) continue;
        ans += dfs_cnt(u);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, q;
    cin >> N >> m >> q;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        ed[a].emplace_back(b, i);
        ed[b].emplace_back(a, i);
    }
    bicomps();
    init(N);
    rep(i, 0, N) if (color[i]==-1)
        make_tree(i, i);
    //rep(i, 0, N) cout << i << "-color: " << color[i] << endl;
    rep(i, 0, m) bridge[i] = 0;
    rep(i, 0, N) h[i] = -1;
    rep(i, 0, N)
        if (h[color[i]]==-1)
            dfs_lca(color[i]);
    int K=1;
    while (q--) {
        int ni, mi;
        cin >> ni >> mi;
        vi nodes, cl;
        rep(i, 0, ni) {
            int x;
            cin >> x;
            x = rotate(x);
            x--;
            nodes.push_back(color[x]);
        }
        sort(all(nodes));
        nodes.erase(unique(all(nodes)), nodes.end());
        cl = nodes;
        vector<pii> edges;
        rep(i, 0, mi) {
            int x, y;
            cin >> x >> y;
            x = rotate(x);
            y = rotate(y);
            //cout << "aristas: " << x << " " << y << " " << R << endl;
            x--; y--;
            cl.push_back(color[x]);
            cl.push_back(color[y]);
            edges.emplace_back(color[x], color[y]);
        }
        sort(all(cl), [&](int u, int v) {
            return lo[u] < lo[v];
        });
        cl.erase(unique(all(cl)), cl.end());
        eid=0;
        for (int i = 0; i < sz(cl); ++i) {
            int j = i;
            while (j+1 < sz(cl) 
                && comp_id[cl[i]] == comp_id[cl[j+1]]) j++;
            auxiliary_tree(vi(cl.begin()+i, cl.begin()+j+1));
            i = j;
        }
        for (auto [u, v] : edges) {
            //cout << u << " " << v << endl;
            aux[u].emplace_back(v, eid);
            aux[v].emplace_back(u, eid++);
        }
        for (int i = 0 ; i < eid; ++i) bridge[i]=0;
        trav(v, nodes) {
            need[v] = 1;
            if (!num[v]) dfs(aux, bridge, v, -1);
        }
        int ans = dfs_cnt(nodes[0]);
        //cout << ans << " " << sz(nodes) << endl;
        if (ans == sz(nodes)) cout << "YES\n", R=(R+K)%N;
        else cout << "NO\n";
        trav(v, nodes) need[v] = 0;
        K++;
    }
    return 0;
}