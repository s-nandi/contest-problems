// prob (linearity of exp.), combo (dp to solve recurrence), lca-related ideas
// https://codeforces.com/contest/1540/problem/B

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

ll euclid(ll a, ll b, ll &x, ll &y) {
  if (b) { ll d = euclid(b, a % b, y, x);
    return y -= a/b * x, d; }
  return x = 1, y = 0, a;
}

const ll mod = 1'000'000'007; // change to something else
struct Mod {
  ll x;
  Mod(ll xx) : x(xx) {}
  Mod operator+(Mod b) { return Mod((x + b.x) % mod); }
  Mod operator-(Mod b) { return Mod((x - b.x + mod) % mod); }
  Mod operator*(Mod b) { return Mod((x * b.x) % mod); }
  Mod operator/(Mod b) { return *this * invert(b); }
  Mod invert(Mod a) {
    ll x, y, g = euclid(a.x, mod, x, y);
    assert(g == 1); return Mod((x + mod) % mod);
  }
  Mod operator^(ll e) {
    if (!e) return Mod(1);
    Mod r = *this ^ (e / 2); r = r * r;
    return e&1 ? *this * r : r;
  }
};

constexpr auto MAXN = 200;
constexpr auto INF = 1031231234;
auto memo = vector(MAXN + 5, vector(MAXN + 5, -1));

ll recur(int a, int b) { // prob(a L's complete before b R's)
  if (a == 0) return 1LL;
  if (b == 0) return 0LL;
  if (memo[a][b] == -1) {
    auto p1 = recur(a - 1, b);
    auto p2 = recur(a, b - 1);
    auto res = (Mod{p1} + Mod{p2}) / Mod{2};
    memo[a][b] = res.x;
  }
  return memo[a][b];
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  auto mat = vector(n, vector(n, INF));
  rep(it, 0, n - 1) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    mat[u][v] = mat[v][u] = 1;
  }
  rep(k, 0, n) rep(i, 0, n) rep(j, 0, n)
    mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
  
  Mod res{0};
  rep(root, 0, n) {
    rep(i, 0, n) rep(j, 0, i) { // i before j
      auto from_root_dist = mat[root][i] + mat[root][j];
      auto between_dist = mat[i][j];
      auto above = (from_root_dist - between_dist) / 2;
      auto idist = mat[root][i] - above;
      auto jdist = mat[root][j] - above;
      res = res + recur(idist, jdist);
    }
  }
  res = res / n;
  cout << res.x << '\n';
}
