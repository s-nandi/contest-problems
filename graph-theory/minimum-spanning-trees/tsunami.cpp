// minimum spanning tree, sweep line
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=582&page=show_problem&problem=4210
// 2012 Mid-Atlantic Regional

#include <bits/stdc++.h>

using namespace std;

struct pt {
  int x, y;

  auto operator<(const pt& o) const -> bool { return tie(y, x) < tie(o.y, o.x); }
  auto distance(const pt& o) const -> double {
    auto dx = x - o.x;
    auto dy = y - o.y;
    return sqrt(dx * dx + dy * dy);
  }
};

auto distance_to_processed(const pt& p, const vector<pt>& processed) -> double {
  auto closest = p.distance(processed[0]);
  for (const auto& q : processed) closest = min(closest, p.distance(q));
  return closest;
}

struct disjoint_set_union {
  vector<int> par;

  disjoint_set_union(int sz) : par(sz) { iota(begin(par), end(par), 0); }
  auto component(int i) -> int { return par[i] == i ? i : (par[i] = component(par[i])); }
  auto merge(int i, int j) -> void { par[component(i)] = component(j); }
  auto same_component(int i, int j) -> bool { return component(i) == component(j); }
};

template <typename edge_t>
auto kruskal(int num_nodes, const vector<edge_t>& edge_list) -> double {
  auto result = 0.0;
  auto edges = edge_list;
  sort(begin(edges), end(edges));
  auto components = disjoint_set_union(num_nodes);
  for (const auto& edge : edges) {
    auto weight = get<0>(edge);
    auto i = get<1>(edge);
    auto j = get<2>(edge);
    if (!components.same_component(i, j)) {
      result += weight;
      components.merge(i, j);
    }
  }
  return result;
}

using mst_edge = tuple<double, int, int>;

int main() {
  int n;
  while (true) {
    cin >> n;
    if (n == 0) break;

    auto points = vector<pt>(n);
    for (auto& point : points) cin >> point.x >> point.y;
    sort(begin(points), end(points));

    auto cost = 0.0;
    auto processed = vector<pt>{};
    for (int it = 0; it < points.size();) {
      auto current = vector<pt>{};
      auto level = points[it].y;
      while (it < points.size() and points[it].y == level) {
        current.push_back(points[it]);
        it++;
      }

      auto num_nodes = current.size();
      auto edge_list = vector<mst_edge>{};
      if (!processed.empty()) {
        num_nodes++;
        auto root = num_nodes - 1;
        for (int i = 0; i < current.size(); i++)
          edge_list.push_back({distance_to_processed(current[i], processed), root, i});
      }
      for (int i = 0; i < current.size(); i++) {
        for (int j = 0; j < current.size(); j++) {
          edge_list.push_back({current[i].distance(current[j]), i, j});
        }
      }
      cost += kruskal(num_nodes, edge_list);
      move(begin(current), end(current), back_inserter(processed));
    }
    cout << fixed << setprecision(2) << cost << '\n';
  }
}
