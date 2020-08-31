// dp, greedy (casework)
// https://codeforces.com/contest/1396/problem/C

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

constexpr ll INF = 1e18;
bool minn(auto& a, auto b){return b < a ? (a = b, true) : false;}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  ll x, y, z, d;
  cin >> x >> y >> z >> d;
  vector<ll> a(n);
  trav(i, a) cin >> i;

  vector<ll> dp(n + 1, INF);
  dp[0] = 0;
  // ak => wipe out everything (including boss) in level before moving to next cell via a[i] pistols and AWP
  // laser => wipe out all minions and damage boss for 1 hp via laser OR (a[i] + 1) pistols
  // mostly 2 choices (and minor cases when nearing end): AK and move to next, or laser current/next cells which incurs 2d extra cost and move to i+2
  rep(i, 0, n) {
    auto possible_ak = (ll) a[i] * x + z + d;
    minn(dp[i + 1], dp[i] + possible_ak);
    auto mybest = min<ll>(y, (ll)(a[i] + 1) * x);
    if (i + 1 < n) {
      auto theirbest = min<ll>(y, (ll)(a[i + 1] + 1) * x);
      auto possible_laser_laser = (ll) mybest + theirbest + 4LL * d + x + x;
      minn(dp[i + 2], dp[i] + possible_laser_laser);
      if (i + 1 == n - 1) {
        auto possible_laser_ak = (ll) mybest + d + (ll)(a[i + 1] * x + z) + d + x + d; // overcount d since compensated later
        minn(dp[i + 2], dp[i] + possible_laser_ak);
      }
    } else {
      auto possible_laser = (ll) mybest + 2 * d + x + d; // overcount d since compensated later
      minn(dp[i + 1], dp[i] + possible_laser);
    }

  }
  cout << (dp[n] - d) << '\n'; // compensate for the extra d cost to go to sentinel state
}
