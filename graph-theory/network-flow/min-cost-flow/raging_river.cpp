// min cost max flow (maximum # of edge-disjoint paths w/ minimum total edge weight)
// https://open.kattis.com/problems/ragingriver
// 2018 South Central USA Regional

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr auto INF = 1231231234;

struct edge {
  int to, id;
};
typedef vector<vector<edge>> graph;

typedef ll flowT;
typedef ll costT;
struct minCostMaxFlow {
  int sz;
  graph g;
  vector<flowT> capacities, flow, sent;
  vector<costT> costs, distances;
  vector<int> prev, pid, inq;

  minCostMaxFlow(int s)
      : sz(s), g(sz), sent(sz), distances(sz), prev(sz), pid(sz), inq(sz) {}

  void addEdge(int from, int to, flowT capacity, costT cost) {
    g[from].push_back({to, (int)flow.size()});
    capacities.push_back(capacity), flow.push_back(0), costs.push_back(cost);
    g[to].push_back({from, (int)flow.size()});
    capacities.push_back(0), flow.push_back(0), costs.push_back(-cost);
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
        if (residual(e.id) > 0 and
            distances[curr] + costs[e.id] < distances[e.to]) {
          distances[e.to] = distances[curr] + costs[e.id];
          prev[e.to] = curr, pid[e.to] = e.id;
          sent[e.to] = min(sent[curr], residual(e.id));
          if (!inq[e.to])
            q.push(e.to), inq[e.to] = true;
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
      if (f == target)
        break;
    }
    return {f, cost};
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int p, r, l;
  cin >> p >> r >> l;

  int num_nodes = r + 3;
  int super_source = num_nodes - 3, source = num_nodes - 2,
      sink = num_nodes - 1;

  auto node_index = [=](int i) {
    if (i == -2) {
      return source;
    } else if (i == -1) {
      return sink;
    }
    return i;
  };

  auto nf = minCostMaxFlow(num_nodes);

  nf.addEdge(super_source, source, p, 0);
  for (int i = 0; i < l; i++) {
    int from, to;
    cin >> from >> to;

    from = node_index(from);
    to = node_index(to);

    nf.addEdge(from, to, 1, 1);
    nf.addEdge(to, from, 1, 1);
  }

  auto [flow, cost] = nf.maxflow(super_source, sink);
  if (flow < p) {
    auto rem = p - flow;
    cout << rem << " people left behind" << '\n';
  } else {
    cout << cost << '\n';
  }
}
