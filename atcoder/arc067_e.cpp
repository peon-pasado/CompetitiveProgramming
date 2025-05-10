/**
 * @author Miguel Mini
 * @tag fft, combinatorics
 * @idea:
 *
 *      - we need sum of:
 *
 *          multi-binomial(n, {A (x_A), ..., B (x_B)})
 *
 *          divide by (x_A! x ... x_B!)
 *
 *          with C <= x_A <= D.
 *
 *      - we can use P_i(x) = 1 + (X^A / A!)^i / i! (for i in [C, D])
 *
 *      - we need n-th coefficient of prod_{i\in [A, B]} P_i(x)
 *
 * @complexity O(n \log n)
 */
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;


typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C>& a) {
    int n = sz(a), L = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1);
    static vector<C> rt(2, 1);  // (^ 10% faster if double)
    for (static int k = 2; k < n; k *= 2) {
        R.resize(n); rt.resize(n);
        auto x = polar(1.0L, M_PIl / k); // M_PI, lower-case L
        rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
    }
    vi rev(n);
    rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
                // C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
                auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
                C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
}

typedef vector<ll> vl;
template<int M> vl convMod(const vl &a, const vl &b) {
    if (a.empty() || b.empty()) return {};
    vl res(sz(a) + sz(b) - 1);
    int B=32-__builtin_clz(sz(res)), n=1<<B, cut=int(sqrt(M));
    vector<C> L(n), R(n), outs(n), outl(n);
    rep(i,0,sz(a)) L[i] = C((int)a[i] / cut, (int)a[i] % cut);
    rep(i,0,sz(b)) R[i] = C((int)b[i] / cut, (int)b[i] % cut);
    fft(L), fft(R);
    rep(i,0,n) {
        int j = -i & (n - 1);
        outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
        outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
    }
    fft(outl), fft(outs);
    rep(i,0,sz(res)) {
        ll av = ll(real(outl[i])+.5), cv = ll(imag(outs[i])+.5);
        ll bv = ll(imag(outl[i])+.5) + ll(real(outs[i])+.5);
        res[i] = ((av % M *1ll* cut + bv) % M *1ll* cut + cv) % M;
    }
    return res;
}

const int mod = 1e9 + 7;
const int maxn = 1e3 + 10;
int f[maxn], r[maxn], rf[maxn];

int mul(ll a, ll b) {
    return a*b%mod;
}

int add(int a, int b) {
    return (a+b)%mod;
}

int ex(int a, int b) {
    int r = 1;
    while (b > 0) {
        if (b&1) r = mul(r, a);
        a = mul(a, a);
        b >>= 1;
    }
    return r;
}

vector<ll> x[maxn];

int main() {
    f[0] = rf[0] = r[1] = 1;
    for (int i = 1; i < maxn; ++i) {
        if (i > 1) r[i] = mul(r[mod%i], mod - mod/i);
        f[i] = mul(f[i-1], i);
        rf[i] = mul(rf[i-1], r[i]);
    }
    int n, a, b, c, d;
    cin >> n >> a >> b >> c >> d;
    for (int i = a; i <= b; ++i) {
        x[i].resize(n + 1);
        x[i][0] = 1;
        int e = ex(rf[i], c);
        for (int j = c; j <= d && i * j <= n; ++j) {
            x[i][i * j] = mul(e, rf[j]);
            e = mul(e, rf[i]);
        }
    }
    for (int i = b-1; i >= a; --i) {
        x[i] = convMod<mod>(x[i], x[i+1]);
        if (x[i].size() > n+1) {
            x[i].resize(n+1);
        }
    }
    x[a].resize(n+1);
    cout << mul(f[n], x[a][n]) << endl;
    return 0;
}