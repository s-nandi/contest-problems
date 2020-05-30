// segment tree (matrix mult range query), continued fraction to matrix conversion, k + 1 / (a/b) is simplified if a/b is simplified
// https://dmoj.ca/problem/dmopc19c7p4

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define sz(x) (int)(x).size()

const int MOD = 1000000007;
int mult(ll a, ll b){return a * b % MOD;}
void self_add(int& a, int b){a = ((ll) a + b) % MOD;}

struct matrix {
  array<array<int, 2>, 2> mat{};
  matrix(bool identity = false){mat[0][0] = mat[1][1] = identity;}
  matrix(int v) : mat{{{v, 1}, {1, 0}}} {}
};

matrix operator * (const matrix& a, const matrix& b) {
  matrix c{};
  rep(i, 0, 2) rep(k, 0, 2) rep(j, 0, 2)
    self_add(c.mat[i][j], mult(a.mat[i][k], b.mat[k][j]));
  return c;
}

struct ST {
  using T = matrix;
  T f(const T& a, const T& b){return a * b;}
  int s;
  vector<T> v;
  ST(const vi& vec) : s{sz(vec)}, v(2 * s) {
    rep(i, s, 2 * s) v[i] = T(vec[i - s]);
    for (int i = s - 1; i >= 1; i--)
      v[i] = f(v[2 * i], v[2 * i + 1]);
  }
  T query(int l, int r) {
    T lacc{true}, racc{true};
    for (l += s, r += s; l <= r; (++l) >>= 1, (--r) >>= 1) {
      if (l & 1) lacc = f(lacc, v[l]);
      if (~r & 1) racc = f(v[r], racc);
    }
    return f(lacc, racc);
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;
  vi a(n);
  trav(i, a) cin >> i;
  ST st(a);
  rep(it, 0, q) {
    int l, r;
    cin >> l >> r;
    --l; --r;
    auto res = st.query(l, r);
    rep(i, 0, 2) cout << res.mat[i][0] << " "; cout << '\n';
  }
}
