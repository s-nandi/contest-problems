// prefix sum, maximum two elements with distinct colors, fix right bound of interval
// https://codeforces.com/contest/1364/problem/A
// Note: editorial solution is much simpler/uses problem-specific observations

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using ii = pair<int, int>;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

const int INF = 1031231234;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);


  int T;
  cin >> T;
  while(T--) {
    int n, x;
    cin >> n >> x;
    vi a(n);
    trav(i, a) cin >> i;

    if (x == 1) {
      cout << -1 << '\n';
      continue;
    }

    vector<ll> ps(n);
    rep(i, 0, n) {
      ps[i] = i ? ps[i - 1] + a[i] : a[i];
    }
    auto sum = [&](int l, int r){return l ? ps[r] - ps[l - 1] : ps[r];};

    array<ii, 2> best2{};
    best2[0] = {-1, 0};
    best2[1] = {INF, 1};
    int sol = -1;
    rep(i, 0, n) {
      int possible = 0;
      auto have = sum(0, i) % x;      
      if (best2[0].second == have) {
        possible = i - best2[1].first;
      } else {
        possible = i - best2[0].first;
      }
      sol = max(sol, possible);
      ii curr = {i, have};
      if (curr < best2[0]) {
        if (curr.second != best2[0].second) {
          best2[1] = best2[0];
          best2[0] = curr;
        } else {
          best2[0] = curr;
        }
      } else if (curr < best2[1] and curr.second != best2[0].second) {
        best2[1] = curr;
      }
    }
    cout << sol << '\n';
  }
}
