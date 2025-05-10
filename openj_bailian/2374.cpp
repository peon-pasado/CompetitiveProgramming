/*
 © 2022-05-03 13:13:19 Franco1010 All Rights Reserved
*/

// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>
#define f first
#define s second
#define fore(i,a,b) for(int i = (a), ThxMK = (b); i < ThxMK; ++i)
#define pb push_back
#define all(s) begin(s), end(s)
#define _ ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define sz(s) int(s.size())
#define ENDL '\n'
using namespace std;
typedef long double ld;
typedef long long lli;
typedef pair<lli,lli> ii;
typedef vector<lli> vi;
#define deb(x) cout << #x": " << (x) << endl;


const lli INF = 1e18;
struct Segtree{
  #define mid (l + r) / 2
  #define left(u) (u + 1)
  #define right(u) (u + ((mid - l + 1) << 1))
  struct Node{
    lli l, r, z;
    lli tam;
    Node(lli l = INF, lli r = INF, lli tam = 0, lli z = -1): l(l), r(r), tam(tam), z(z) {}
    Node operator + (const Node &n) {
      return Node(
        min({l, n.l + tam, r + tam - 1, n.r + tam + n.tam - 1}), 
        min({n.r, r + n.tam, n.l + n.tam - 1, l + tam + n.tam - 1}), 
        tam + n.tam);
    }
  };
  vector<Node> st;
  Segtree(lli n): st(2 * n) {}
  void build(int u, int l, int r){
    if(l == r){
      st[u].tam = 1;
      st[u].l = st[u].r = INF;
      return;
    }
    build(left(u), l, mid);
    build(right(u), mid + 1, r);
    st[u] = st[left(u)] + st[right(u)];
  }
  void push(int u, int l, int r){
    if(st[u].z != -1){
      if(l < r){
        st[left(u)].z = st[u].z;
        st[right(u)].z = st[u].z;
      }
      st[u].l = st[u].r = st[u].z;
      st[u].z = -1;
    }
  }
  void update(int u, int l, int r, int ll, int rr, lli val){
    push(u, l, r);
    if(l > r or ll > rr or r < ll or l > rr) return;
    if(ll <= l and r <= rr){
      st[u].z = val;
      push(u, l, r);
      return;
    }
    update(left(u), l, mid, ll, rr, val);
    update(right(u), mid + 1, r, ll, rr, val);
    st[u] = st[left(u)] + st[right(u)];
  }
  Node query(int u, int l, int r, int ll, int rr){
    push(u, l, r);
    if(l > r or ll > rr or r < ll or l > rr) return Node();
    if(ll <= l and r <= rr) return st[u];
    return query(left(u), l, mid, ll, rr) + query(right(u), mid + 1, r, ll, rr);
  }
};

const lli N = 1e5 + 5;

int main(){ _
  // freopen("file.in","r",stdin);
  // freopen("file.out","w",stdout);
  lli n, s; cin >> n >> s;
  Segtree st(2 * N + 1);
  st.build(0, 0, 2 * N);
  st.update(0, 0, 2 * N, s + N, s + N, 0);
  vector<ii> v(n); 
  for(int i = 0; i < n; ++i) cin >>v[i].f >> v[i].s, v[i].f += N, v[i].s += N;
  reverse(all(v));
  for(int i = 0; i < n; ++i){
    int l = v[i].first;
    int r = v[i].second;
    auto foo = st.query(0, 0, 2 * N, l, r);
    st.update(0, 0, 2 * N, l, r, INF);
    st.update(0, 0, 2 * N, l, l, foo.l);
    st.update(0, 0, 2 * N, r, r, foo.r);
  }
  lli foo = st.query(0, 0, 2 * N, 0, N).r;
  lli bar = st.query(0, 0, 2 * N, N, 2 * N).l;
  cout << min(foo, bar) << ENDL;
  return 0;
}

/*

5 4 3 2 1 0 1 2 3 4 5
      2     1
    1     2 1

*/