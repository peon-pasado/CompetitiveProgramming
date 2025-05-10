#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll add(ll a, ll b, ll m) {
  return (a+b)%m;
}

ll mul(ll a, ll b, ll m) {
  ll r = 0;
  while (b > 0) {
    if (b&1) r = add(r, a, m);
    a = add(a, a, m);
    b >>= 1;
  }
  return r;
}

using matrix = vector<vector<ll>>;

matrix mul(matrix A, matrix B, ll m) {
  matrix R(2, vector<ll>(2));
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      for (int k = 0; k < 2; ++k) {
        R[i][j] = add(R[i][j], mul(A[i][k], B[k][j], m), m);
      }
    }
  }
  return R;
}

matrix ex(matrix A, ll n, ll m) {
  matrix R(2, vector<ll>(2));
  R[0][0] = R[1][1] = 1;
  while (n > 0) {
    if (n&1) R = mul(R, A, m);
    A = mul(A, A, m);
    n >>= 1;
  }
  return R;
}

int main() {
  matrix RE(2, vector<ll>(2));
  ll a, n, m;
  cin >> a >> n >> m;
  RE[0][0] = a;
  RE[1][0] = a;
  RE[1][1] = 1;
  matrix REn = ex(RE, n, m);
  ll p_0 = 1, s_0 = 1;
  ll p_n = add(mul(REn[0][0], p_0, m), mul(REn[0][1], s_0, m), m);
  ll s_n = add(mul(REn[1][0], p_0, m), mul(REn[1][1], s_0, m), m);
  cout << s_n << endl;
  return 0;
}