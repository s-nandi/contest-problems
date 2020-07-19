// prefix sums, greedy (only 1 flower needs to be repeated), binary search
// https://codeforces.com/contest/1379/problem/C

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

ll f(ll cnt, ll a, ll b) {
  return a + b * (cnt - 1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while(T--) {
    int n, m;
    cin >> n >> m;
    
    vector<pii> ab(m);
    rep(i, 0, m) cin >> ab[i].first >> ab[i].second;
    auto bya = ab;
    sort(all(bya));
    
    ll res = 0;
    if (n <= m) {
      ll acc = 0;
      rep(i, m - n, m) acc += bya[i].first; // <= 1 of each
      res = max(res, acc);
    }
    
    vector<ll> suff(m);
    for (int i = m - 1; i >= 0; i--)
      suff[i] = i + 1 < m ? suff[i + 1] + bya[i].first : bya[i].first;
    
    rep(i, 0, m) {
      int it = upper_bound(all(bya), ab[i].second, [](const int& a, const pii&b ){
                                                     return a < b.first;
                                                   }) - begin(bya);
      if (sz(bya) - it >= n) continue; // taken care of earlier
      auto others = it < sz(bya) ? suff[it] : 0LL;
      bool overcounted = ab[i].first > ab[i].second;
      int acnt = sz(bya) - it - overcounted;
      auto penalty = overcounted ? ab[i].first : 0LL;
      auto here = (n - acnt) ? f(n - acnt, ab[i].first, ab[i].second) : 0LL;
      auto possible = others - penalty + here;
      res = max(res, possible);
    }
    cout << res << '\n';
  }
}
