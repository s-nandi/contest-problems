// matrix exponentiation, fermat's little theorem (exponents should be found mod MOD-1, not mod MOD), exponents follow linear recurrence => find exps then binary exponentiate
// https://codeforces.com/contest/1182/problem/E

#include <bits/stdc++.h>
using namespace std;
 
#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;
 
const int MOD = 1'000'000'007;
 
using matT = ll;
using matrix = vector<vector<matT>>;
 
int add(ll a, ll b, int mod) {return (a + b) % mod;}
int mult(ll a, ll b, int mod){return a * b % mod;}
 
matrix make_matrix(int n, int m, matT val = 0) {return vector(n, vector(m, val));}
 
matrix mult(const matrix& a, const matrix& b, int mod) {
  int n = sz(a), m = sz(a[0]), o = sz(b[0]);
  assert(m == sz(b));
  auto res = make_matrix(n, o);
  rep(i, 0, n) rep(j, 0, m) rep(k, 0, o)
    res[i][k] = add(res[i][k], mult(a[i][j], b[j][k], mod), mod);
  return res;
}
 
matrix exp(matrix mat, ll p, int mod) {
  int n = sz(mat);
  auto res = make_matrix(n, n);
  rep(i, 0, n) res[i][i] = 1LL;
  for (; p; p >>= 1, mat = mult(mat, mat, mod))
    if (p & 1) res = mult(res, mat, mod);
  return res;
}
 
int exp(ll a, ll p, int mod) {
  auto res = 1;
  for (; p; p >>= 1, a = mult(a, a, mod))
    if (p & 1) res = mult(res, a, mod);
  return res;
}
 
int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
 
  ll n, c;
  vector<ll> fs(3);
  cin >> n;
  trav(f, fs) cin >> f;
  cin >> c;
 
  matrix mat1{{1, 1, 1, 1, 0},
              {1, 0, 0, 0, 0},
              {0, 1, 0, 0, 0},
              {0, 0, 0, 1, 2},
              {0, 0, 0, 0, 1}
  };
  matrix mat2{
              {1, 1, 1},
              {1, 0, 0},
              {0, 1, 0}
  };
 
  auto cmat = exp(mat1, n - 3, MOD - 1);
  auto fmat = exp(mat2, n - 3, MOD - 1);
 
  matrix cvec = {{0}, {0}, {0}, {2}, {1}};
  vector<matrix> fvecs = {
                          {{0}, {0}, {1}}, // top is f3, bottom is f1
                          {{0}, {1}, {0}},
                          {{1}, {0}, {0}}
  };
  
  int res = 1;
  auto cpower = mult(cmat, cvec, MOD - 1);
  res = mult(res, exp(c, cpower[0][0], MOD), MOD);
  rep(i, 0, 3) {
    auto fipower = mult(fmat, fvecs[i], MOD - 1);
    res = mult(res, exp(fs[i], fipower[0][0], MOD), MOD);
  }
  cout << res << '\n';
}
