// min cost max flow, vertex capacities
// https://open.kattis.com/problems/catering
// 2015 World Finals

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr ll INF = 1000000000;

struct edge {int to, id;};
typedef vector<vector<edge>> graph;

typedef ll flowT;
typedef ll costT;
struct minCostMaxFlow {
  int sz;
  graph g;
  vector<flowT> capacities, flow, sent;
  vector<costT> costs, distances;
  vector<int> prev, pid, inq;

  minCostMaxFlow(int s) : sz(s), g(sz), sent(sz), distances(sz), prev(sz), pid(sz), inq(sz) {}

  auto add_edge(int from, int to, flowT capacity, costT cost) {
    g[from].push_back({to, (int)flow.size()});
    capacities.push_back(capacity), flow.push_back(0), costs.push_back(cost);
    g[to].push_back({from, (int)flow.size()});
    capacities.push_back(0), flow.push_back(0), costs.push_back(-cost);
    return capacities.size() - 2;
  }

  flowT residual(int id) { return capacities[id] - flow[id]; }

  ll spfa(int s, int t) {
    fill(sent.begin(), sent.end(), INF);
    fill(distances.begin(), distances.end(), INF);
    fill(inq.begin(), inq.end(), 0);

    queue<int> q;
    q.push(s);
    distances[s] = 0, inq[s] = true;
    while (!q.empty()) {
      int curr = q.front();
      q.pop();

      inq[curr] = false;
      for (edge e : g[curr])
        if (residual(e.id) > 0 and distances[curr] + costs[e.id] < distances[e.to]) {
          distances[e.to] = distances[curr] + costs[e.id];
          prev[e.to] = curr, pid[e.to] = e.id;
          sent[e.to] = min(sent[curr], residual(e.id));
          if (!inq[e.to]) q.push(e.to), inq[e.to] = true;
        }
    }
    return distances[t] < INF ? sent[t] : 0;
  }

  pair<flowT, costT> maxflow(int source, int sink, flowT target = INF) {
    flowT f = 0, delta;
    costT cost = 0;
    while (delta = spfa(source, sink)) {
      delta = min(delta, target - f);
      f += delta;
      for (int i = sink; i != source; i = prev[i]) {
        auto id = pid[i];
        flow[id] += delta;
        flow[id ^ 1] -= delta;
        cost += costs[id] * delta;
      }
      if (f == target) break;
    }
    return {f, cost};
  }
};

int main() {
  int n, k;
  cin >> n >> k;
  auto num_locations = n + 1;
  auto num_teams = k;

  auto costs = vector(num_locations, vector<long long>(num_locations));
  for (int from = 0; from < num_locations; from++)
    for (int to = from + 1; to < num_locations; to++)
      cin >> costs[from][to];
  auto num_nodes = 2 * num_locations + 2;
  auto source = num_nodes - 2, sink = num_nodes - 1;
  auto mcmf = minCostMaxFlow(num_nodes);

  long long offset_cost = INF;
  auto location_in = [&](int location) { return location; };
  auto location_out = [&](int location) { return num_locations + location; };

  mcmf.add_edge(source, location_out(0), num_teams, 0);
  for (int from = 0; from < num_locations; from++)
    for (int to = from + 1; to < num_locations; to++)
      mcmf.add_edge(location_out(from), location_in(to), INF, costs[from][to]);
  for (int loc = 0; loc < num_locations; loc++)
    mcmf.add_edge(location_in(loc), location_out(loc), 1, -offset_cost);
  for (int from = 0; from < num_locations; from++)
      mcmf.add_edge(location_out(from), sink, INF, 0);

  auto [max_flow, min_cost] = mcmf.maxflow(source, sink);
  min_cost += (long long)(num_locations - 1) * offset_cost;
  cout << min_cost << '\n';
}
