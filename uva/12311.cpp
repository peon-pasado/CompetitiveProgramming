#include <bits/stdc++.h>
using namespace std;

const int maxn = 30005;
int x[maxn], y[maxn];

using i32 = std::int32_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using isize = std::ptrdiff_t;
using usize = std::size_t;

template <class Select>
std::vector<usize> smawk(const usize row_size, const usize col_size,
                         const Select &select) {
  using vec_zu = std::vector<usize>;

  const std::function<vec_zu(const vec_zu &, const vec_zu &)> solve =
      [&](const vec_zu &row, const vec_zu &col) -> vec_zu {
    const usize n = row.size();
    if (n == 0)
      return {};
    vec_zu c2;
    for (const usize i : col) {
      while (!c2.empty() && select(row[c2.size() - 1], c2.back(), i))
        c2.pop_back();
      if (c2.size() < n)
        c2.push_back(i);
    }
    vec_zu r2;
    for (usize i = 1; i < n; i += 2)
      r2.push_back(row[i]);
    const vec_zu a2 = solve(r2, c2);
    vec_zu ans(n);
    for (usize i = 0; i != a2.size(); i += 1)
      ans[i * 2 + 1] = a2[i];
    usize j = 0;
    for (usize i = 0; i < n; i += 2) {
      ans[i] = c2[j];
      const usize end = i + 1 == n ? c2.back() : ans[i + 1];
      while (c2[j] != end) {
        j += 1;
        if (select(row[i], ans[i], c2[j]))
          ans[i] = c2[j];
      }
    }
    return ans;
  };
  vec_zu row(row_size);
  std::iota(row.begin(), row.end(), 0);
  vec_zu col(col_size);
  std::iota(col.begin(), col.end(), 0);
  return solve(row, col);
}

int n;

int64_t f(int i, int j)  {
    j %= n;
    return (x[i] - x[j]) *1ll* (x[i] - x[j]) + (y[i] - y[j])*1ll*(y[i] - y[j]); 
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    while (cin>>n, n > 0) {
        for (int i=0; i<n; ++i) {
            cin>>x[i]>>y[i];
        }
        const auto select = [&](const usize i, const usize j, const usize k) {
            //concave: return A[i][j] <= A[i][k]; max
            //convex: return A[i][j] > A[j][k]; min 
            return f(i, j) <= f(i, k);  
        };
        auto res = smawk(n, 2 * n, select);
        for (int i=0; i<n; ++i) {
            cout << res[i] % n + 1 << '\n';
        }
    }
    return 0;
}