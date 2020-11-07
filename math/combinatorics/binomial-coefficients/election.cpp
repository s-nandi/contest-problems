// nck (via factorization of n/k, cancel out denominator factors from numerator factors), combo (calc # of ways to end with an exact # of votes and fix this value)
// https://open.kattis.com/problems/election
// 2016 Rocky Mountain Regional

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
#define cauto const auto&
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

const string LOST = "RECOUNT!";
const string UNSURE = "PATIENCE, EVERYONE!";
const string WIN = "GET A CRATE OF CHAMPAGNE FROM THE BASEMENT!";

constexpr int MAXN = 50;

vi factors[MAXN + 1];

ll nck(ll n, ll k) { // no overflow since we know the result is < 2^(MAXN + 1) (sum of pascal triangle row MAXN)
  if (k < 0 or k > n) return 0;
  map<int, int> freq;
  rep(val, 1, n + 1) trav(i, factors[val]) freq[i]++;
  rep(val, 1, k + 1) trav(i, factors[val]) freq[i]--;
  rep(val, 1, n - k + 1) trav(i, factors[val]) freq[i]--;
  ll res = 1LL;
  for (cauto [fac, cnt]: freq) {
    rep(it, 0, cnt) res *= fac;
  }
  return res;
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  rep(i, 2, MAXN + 1) {
    auto curr = i;
    rep(j, 2, i + 1) {
      while (curr % j == 0) {
        factors[i].PB(j);
        curr /= j;
      }
      if (curr == 1) break;
    }
  }
    
  int T;
  cin >> T;
  while(T--) {
    int n, v1, v2, w;
    cin >> n >> v1 >> v2 >> w;
    auto threshold = (n / 2) + 1;
    auto m = v1 + v2;
    auto rem = n - m;

    /*
     * Want to check if [sum_{endwith = threshold}^{n} nck(rem, endwith - alreadyhave) * (1/2)^rem] > w / 100
     * Equivalent to: 100 * [sum_{endwith = threshold}^n nck(rem, endwith - alreadyhave)] > w * 2^rem
     * LHS is stored in tot (multiply by 100 at end), RHS is stored in target
     */
    ll tot = 0;
    rep(endwith, threshold, n + 1)
      tot += nck(rem, endwith - v1);
    tot *= 100;
    
    auto target = (1LL << rem) * w;
    if (tot == 0) cout << LOST << '\n';
    else if (tot > target) cout << WIN << '\n';
    else cout << UNSURE << '\n';
  }
}
