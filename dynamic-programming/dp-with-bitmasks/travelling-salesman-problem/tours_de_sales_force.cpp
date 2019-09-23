// tsp, min cost max flow (int flow and double cost), min perimeter when merging point sets
// https://open.kattis.com/problems/toursdesalesforce
// 2018 East-Central NA Regional

#include <bits/stdc++.h>
using namespace std;

using ptT = double;
struct pt {
    ptT x, y;

    auto dist(const auto& o) const {
        auto dx = x - o.x;
        auto dy = y - o.y;
        return sqrt(dx * dx + dy * dy);
    }
};

constexpr auto MAXN = 16;
double dp[1 << MAXN][MAXN];

template <typename T>
T tsp(vector<vector<T>>& costs, int s) {
    int n = costs.size();

    for (int bm = 0; bm < (1 << n); bm++) {
        for (int i = 0; i < n; i++) {
            dp[bm][i] = numeric_limits<T>::max() / 2;
        }
    }
    for (int i = 0; i < n; i++) dp[1 << i][i] = costs[s][i];

    for (int bm = 1; bm < (1 << n); bm++) {
        for (int i = 0; i < n; i++)
            if (bm & (1 << i)) {
                int sm = bm - (1 << i);
                for (int j = 0; j < n; j++)
                    if (sm & (1 << j)) dp[bm][i] = min(dp[bm][i], dp[sm][j] + costs[j][i]);
            }
    }

    T sol = 0;
    int FULL = (1 << n) - 1;
    for (int i = 0; i < n; i++) {
        auto possible = dp[FULL][i] + costs[i][s];
        if (i == 0 or possible < sol) sol = possible;
    }
    return sol;
}

auto min_tour_length(const vector<pt>& a) {
    int n = a.size();
    auto costs = vector(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            costs[i][j] = a[i].dist(a[j]);
        }
    }
    return tsp(costs, 0);
}

struct edge {
    int to, id;
};
using graph = vector<vector<edge>>;

using flowT = int;
using costT = double;
struct mincost_maxflow {
    int sz;
    graph g;
    vector<flowT> capacities, flow, sent;
    vector<costT> costs, distances;
    vector<int> prev, pid, inq;

    static constexpr auto INF_FLOW = numeric_limits<flowT>::max();
    static constexpr auto INF_COST = numeric_limits<costT>::max() / 2;

    mincost_maxflow(int s) : sz(s), g(sz), sent(sz), distances(sz), prev(sz), pid(sz), inq(sz) {}

    void add_edge(int from, int to, flowT capacity, costT cost) {
        g[from].push_back({to, (int)flow.size()});
        capacities.push_back(capacity), flow.push_back(0), costs.push_back(cost);

        g[to].push_back({from, (int)flow.size()});
        capacities.push_back(0), flow.push_back(0), costs.push_back(-cost);
    }

    flowT residual(int id) { return capacities[id] - flow[id]; }

    auto spfa(int s, int t) {
        fill(begin(sent), end(sent), INF_FLOW);
        fill(begin(distances), end(distances), INF_COST);
        fill(begin(inq), end(inq), 0);

        queue<int> q;
        q.push(s);
        distances[s] = 0;
        inq[s] = true;
        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            inq[curr] = false;

            for (edge e : g[curr])
                if (residual(e.id) > 0 and distances[curr] + costs[e.id] < distances[e.to]) {
                    distances[e.to] = distances[curr] + costs[e.id];
                    // cout << "Distance: " << distances[e.to] << endl;
                    prev[e.to] = curr;
                    pid[e.to] = e.id;
                    sent[e.to] = min(sent[curr], residual(e.id));
                    if (!inq[e.to]) {
                        q.push(e.to), inq[e.to] = true;
                    }
                }
        }
        return distances[t] < INF_COST ? sent[t] : 0;
    }

    auto find_maxflow_mincost(int source, int sink) {
        flowT f = 0, delta;
        costT cost = 0;
        while (delta = spfa(source, sink)) {
            f += delta;
            for (int i = sink; i != source; i = prev[i]) {
                auto id = pid[i];
                flow[id] += delta;
                flow[id ^ 1] -= delta;
                cost += costs[id] * delta;
            }
        }
        return pair{f, cost};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    int h = n / 2;

    double original_length = 0.0;
    vector<vector<pt>> districts(n);
    for (auto& district : districts) {
        int c;
        cin >> c;
        district = vector<pt>(c);
        for (auto& p : district) {
            cin >> p.x >> p.y;
        }
        original_length += min_tour_length(district);
    }

    int num_nodes = n + 2;
    int source = num_nodes - 2, sink = num_nodes - 1;
    auto mcmf = mincost_maxflow(num_nodes);
    for (int i = 0; i < h; i++) {
        mcmf.add_edge(source, i, 1, 0);
    }
    for (int j = h; j < n; j++) {
        mcmf.add_edge(j, sink, 1, 0);
    }
    for (int i = 0; i < h; i++) {
        for (int j = h; j < n; j++) {
            auto merged = vector<pt>{};
            for (auto p : districts[i]) merged.push_back(p);
            for (auto p : districts[j]) merged.push_back(p);
            mcmf.add_edge(i, j, 1, min_tour_length(merged));
        }
    }
    auto [ph, new_length] = mcmf.find_maxflow_mincost(source, sink);
    cout << fixed << setprecision(10) << original_length << " " << new_length << '\n';
}
