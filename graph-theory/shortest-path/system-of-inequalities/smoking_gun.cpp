// reducing inequalities (floyd-warshall), toposort on inequalities
// https://codeforces.com/gym/100729/attachments (problem G)
// 2011 Northwestern European Regional

#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

using ptT = ld;
struct pt {
  ptT x, y;
  auto dist(const auto& o) {
    auto dx = x - o.x, dy = y - o.y;
    return sqrt(dx * dx + dy * dy);
  }
};
constexpr ptT sound = 340;
constexpr ptT INF = 1e9;

auto minn(auto& a, auto b){a = min(a, b);}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
      int n, m;
      cin >> n >> m;
      map<string, int> indexer;
      vector<string> names(n);
      vector<pt> points(n);
      rep(i, 0, n) {
        string s;
        cin >> s;
        indexer[s] = i;
        names[i] = s;
        cin >> points[i].x >> points[i].y;
      }

      vi shot(n);
      auto costs = vector(n, vector<ptT>(n, INF));
      rep(i, 0, n) costs[i][i] = 0;
      rep(i, 0, m) {
        string a, b, c, waste;
        cin >> a >> waste >> b >> waste >> waste >> c;
        int aind = indexer[a], bind = indexer[b], cind = indexer[c];
        auto dist_ab = points[aind].dist(points[bind]);
        auto dist_ac = points[aind].dist(points[cind]);
        minn(costs[cind][bind], dist_ac - dist_ab);
        shot[cind] = shot[bind] = true;
      }
      rep(k, 0, n) rep(i, 0, n) rep(j, 0, n)
        minn(costs[i][j], costs[i][k] + costs[k][j]);

      vi shooters;
      rep(i, 0, n) if (shot[i]) shooters.PB(i);
      if (any_of(all(shooters), [&](int i){return costs[i][i] < 0;})) {
        cout << "IMPOSSIBLE" << '\n';
        continue;
      }
      vi sol;
      int status = 0; // multiple: 2, unique: 0
      while(!shooters.empty()) {
        vi candidates;
        trav(i, shooters) {
          bool valid = all_of(all(shooters),
                              [&](int j){return (i == j) or costs[j][i] < 0;});
          if (valid) candidates.PB(i);
        }
        // no need to check sz(candidates) > 1 since that can only happen
        // if there's a negative cycle (we checked for this earlier)
        if (sz(candidates) == 0) {
          status = 2; break;
        } else {
          int cand = candidates[0];
          sol.PB(cand);
          shooters.erase(find(all(shooters), cand));
        }
      }
      if (status == 0) {
      	trav(i, sol) cout << names[i] << " "; cout << '\n';
      } else 
        cout << "UNKNOWN" << '\n';
    }
}
