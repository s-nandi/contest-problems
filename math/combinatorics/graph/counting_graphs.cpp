// combo (nck), shortest path properties (edge uv => sh[v] <= sh[u] + 1), count # of ways to create tree (sh[i] + 1 == sh[j]) and then # of ways to add redundant edges (sh[i] == sh[j])
// https://www.codechef.com/LTIME87A/problems/CNTGRP

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

const int MOD = 1000000007;
int add(ll a, ll b){return (a + b) % MOD;}
int mult(ll a, ll b){
  if (a >= MOD) a %= MOD;
  if (b >= MOD) b %= MOD;
  return a * b % MOD;
}
int exp(ll a, ll p) {
  int res = 1;
  for (; p; p >>= 1, a = mult(a, a))
    if (p & 1) res = mult(res, a);
  return res;
}
int inv(ll a){return exp(a, MOD - 2);}

int nck(ll n, ll k) {
  if (k > n) return 0;
  int num = 1, denom = 1;
  rep(i, n - k + 1, n + 1) num = mult(num, i);
  rep(i, 1, k + 1) denom = mult(denom, i);
  return mult(num, inv(denom));
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while(T--) {
    int n, m;
    cin >> n >> m;
    vi a(n - 1);
    trav(i, a) cin >> i;
    a.PB(0);
    bool valid = true;
    sort(all(a));
    rep(i, 0, n - 1) {
      if (a[i + 1] - a[i] >= 2) valid = false;
    }
    if (!valid) cout << 0 << '\n';
    else {
      int ways = 1;
      vi cnt(n);
      cnt[0] = 1;
      trav(i, a) {
        if (i == 0) continue;
        ways = mult(ways, cnt[i - 1]);
        cnt[i]++;
      }
      m -= (n - 1);
      ll num_edges = 0;
      rep(i, 1, n)
        num_edges += ((ll) cnt[i] * (cnt[i] - 1)) / 2;
      auto extras = nck(num_edges, m);
      cout << mult(ways, extras) << '\n';
    }
  }
}
