// event sweep, combo, nck mod prime, canonically count sets at right endpoint of to-be removed interval
// https://codeforces.com/contest/1420/problem/D

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

struct edge{int to;};
using graph = vector<vector<edge>>;

const int MAXN = 600'000;
const int MOD = 998244353;

int add(ll a, ll b){return (a + b) % MOD;}
int mult(ll a, ll b){return a * b % MOD;}
int exp(ll a, ll p) {
  ll res = 1;
  for (; p; p >>= 1, a = mult(a, a))
    if (p & 1) res = mult(res, a);
  return res;
}
int inv(ll a){return exp(a, MOD - 2);}

int fac[MAXN + 1], invfac[MAXN + 1];

int nck(int n, int k) {
  if (k > n) return 0;
  auto num = fac[n];
  auto denom = mult(invfac[k], invfac[n - k]);
  return mult(num, denom);
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  fac[0] = 1;
  rep(i, 1, MAXN + 1) fac[i] = mult(fac[i - 1], i);
  rep(i, 0, MAXN + 1) invfac[i] = inv(fac[i]);

  int n, k;
  cin >> n >> k;
  vi l(n), r(n);
  vi sorted;
  rep(i, 0, n) {
    cin >> l[i] >> r[i];
    sorted.PB(l[i]);
    sorted.PB(r[i]);
  }
  sort(all(sorted));
  sorted.erase(unique(all(sorted)), end(sorted));
  auto getindex = [&](int val){return lower_bound(all(sorted), val) - begin(sorted);};

  vi ins(MAXN + 1), rmv(MAXN + 1);
  rep(i, 0, n) {
    l[i] = getindex(l[i]);
    r[i] = getindex(r[i]);
    ins[l[i]]++;
    rmv[r[i]]++;
  }
  ll res = 0;
  int cnt = 0;
  rep(i, 0, MAXN + 1) {
    cnt += ins[i];
    rep(it, 0, rmv[i]) {
      auto delta = nck(cnt - 1, k - 1);
      res = add(res, delta);
      cnt--;
    }
  }
  cout << res << '\n';
}
