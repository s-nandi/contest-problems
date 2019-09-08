// minimum spanning tree, geometry (untangling intersecting lines shortens total length)
// https://open.kattis.com/problems/communicationssatellite
// 2018 South Central USA Regional

#include <bits/stdc++.h>
using namespace std;

using ptT = int;
struct pt {
  ptT x, y;

  auto dist(const pt &o) const {
    auto dx = x - o.x;
    auto dy = y - o.y;
    return sqrt(dx * dx + dy * dy);
  }
};

struct circle {
  pt center;
  int radius;

  auto connection_length(const circle &o) const {
    return center.dist(o.center) - radius - o.radius;
  }
};

using weightT = double;
using edge = tuple<weightT, int, int>;

struct disjointSetUnion {
  int sz;
  vector<int> par;

  disjointSetUnion(int s) {
    sz = s;
    par.resize(sz);
    for (int i = 0; i < sz; i++)
      par[i] = i;
  }

  int findRoot(int i) { return par[i] == i ? i : (par[i] = findRoot(par[i])); }
  void unionElements(int i, int j) { par[findRoot(i)] = findRoot(j); }
  bool sameComponent(int i, int j) { return findRoot(i) == findRoot(j); }
};

int main() {
  int n;
  cin >> n;

  vector<circle> circles(n);
  for (auto &circle : circles) {
    cin >> circle.center.x >> circle.center.y >> circle.radius;
  }

  vector<edge> edges;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      auto weight = circles[i].connection_length(circles[j]);
      edges.push_back({weight, i, j});
    }
  }
  sort(begin(edges), end(edges));

  weightT sol = 0.0;
  auto dsu = disjointSetUnion(n);
  for (const auto &[weight, i, j] : edges) {
    if (!dsu.sameComponent(i, j)) {
      dsu.unionElements(i, j);
      sol += weight;
    }
  }
  cout << fixed << setprecision(11) << sol << '\n';
}
