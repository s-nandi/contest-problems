// max flow (max edge disjoint paths), expanding node/edges into multiple node/edges
// https://open.kattis.com/problems/conveyorbelts
// 2018 Singapore Regional

#include <bits/stdc++.h>
using namespace std;

constexpr auto INF = 1231231234;

struct edge {
    int to, id;
};

using graph = vector<vector<edge>>;

using flowT = int;
struct dinic {
    int sz;
    graph g;
    vector<flowT> capacities, flow;
    vector<int> level, startEdge;

    dinic(int s) : sz(s), g(sz), level(sz), startEdge(sz) {}

    void add_edge(int from, int to, flowT capacity) {
        g[from].push_back({to, (int)flow.size()});
        capacities.push_back(capacity), flow.push_back(0);
        g[to].push_back({from, (int)flow.size()});
        capacities.push_back(0), flow.push_back(0);
    }

    flowT residual(int id) { return capacities[id] - flow[id]; }

    bool buildLevelGraph(int source, int sink) {
        queue<int> q;
        q.push(source);
        fill(level.begin(), level.end(), -1);
        level[source] = 0;
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            for (edge e : g[curr])
                if (level[e.to] == -1 and residual(e.id) > 0) {
                    q.push(e.to);
                    level[e.to] = level[curr] + 1;
                }
        }
        return level[sink] != -1;
    }

    flowT blockingFlow(int curr, int sink, flowT sent = INF) {
        if (curr == sink) return sent;
        for (; startEdge[curr] < g[curr].size(); startEdge[curr]++) {
            edge e = g[curr][startEdge[curr]];
            if (level[e.to] == level[curr] + 1 and residual(e.id) > 0) {
                flowT augment = blockingFlow(e.to, sink, min(sent, residual(e.id)));
                if (augment > 0) {
                    flow[e.id] += augment;
                    flow[e.id ^ 1] -= augment;
                    return augment;
                }
            }
        }
        return 0;
    }

    flowT maxflow(int source, int sink) {
        flowT res = 0;
        while (buildLevelGraph(source, sink)) {
            fill(startEdge.begin(), startEdge.end(), 0);
            while (flowT delta = blockingFlow(source, sink)) res += delta;
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k, m;
    cin >> n >> k >> m;

    graph g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].push_back({b});
    }

    auto num_nodes = n * k + 2;
    auto source = num_nodes - 2, sink = num_nodes - 1;
    auto dnc = dinic(num_nodes);
    auto index = [&](int i, int t) { return i * k + t; };
    for (int i = 0; i < k; i++) {
        dnc.add_edge(source, index(i, i), 1);
    }
    for (int i = 0; i < n; i++) {
        for (auto [to, id] : g[i]) {
            for (int t = 0; t < k; t++) {
                auto next_t = (t + 1) % k;
                dnc.add_edge(index(i, t), index(to, next_t), 1);
            }
        }
    }
    for (int t = 0; t < k; t++) {
        dnc.add_edge(index(n - 1, t), sink, INF);
    }

    auto flow = dnc.maxflow(source, sink);
    cout << flow << '\n';
}
