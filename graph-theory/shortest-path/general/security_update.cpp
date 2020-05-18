// sh. path property (sh[j] <= sh[i] + w_ij forall e_ij), constructive, greedy
// https://codingcompetitions.withgoogle.com/codejam/round/000000000019ffb9/000000000033871f
// 2020 Google Code Jam Round 2

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define PB push_back

struct edge{int to, id;};
using graph = vector<vector<edge>>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  for (int test = 1; test <= T; test++) {
    int n, m;
    cin >> n >> m;
    vi t(n);
    rep(i, 1, n) cin >> t[i];
    graph g(n);
    rep(i, 0, m) {
      int a, b;
      cin >> a >> b;
      --a; --b;
      g[a].PB({b, i});
      g[b].PB({a, i});
    }
    map<int, vi> byposition, byvalue;
    rep(i, 0, n) {
      if (t[i] <= 0) byposition[-t[i]].PB(i);
      else byvalue[t[i]].PB(i);
    }
    vi times(n, -1);
    vi sol(m, -1);
    int fewer = 0;
    int max_time = -1;
    auto relax =
      [&](auto& nodes) {
        trav(i, nodes) {
          trav(e, g[i]) if (times[e.to] != -1) {
            if (times[e.to] < times[i]) sol[e.id] = times[i] - times[e.to];
            else sol[e.id] = 1;
          }
          max_time = max(max_time, times[i]);
          fewer++;
        }
      };
    while (fewer < n) {
      if (!byposition.empty() and begin(byposition) -> first == fewer) {
        auto& curr = begin(byposition) -> second;
        trav(i, curr) times[i] = max_time + 1;
        relax(curr);
        byposition.erase(begin(byposition));
      } else {
        auto& value = begin(byvalue) -> first;
        auto& curr = begin(byvalue) -> second;
        trav(i, curr) times[i] = value;
        relax(curr);
        byvalue.erase(begin(byvalue));
      }
    }
    cout << "Case #" << test << ": ";
    trav(i, sol) cout << i << " "; cout << '\n';
  }
}
