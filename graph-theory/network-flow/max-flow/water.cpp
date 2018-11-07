// max flow (increasing capacities without resetting flow), increasing capacity of non-saturated edge doesn't change max flow
// https://open.kattis.com/problems/water
// 2016 Southeast NA Regional

#include <bits/stdc++.h>

using namespace std;

const int INF = 1231231234;

struct edge{int to, id;};
typedef vector<vector<edge>> graph;
typedef int flowT;

struct dinic
{
    int sz;
    graph g;
    vector <flowT> capacities, flow;
    vector <int> level, startEdge;
    vector <vector<int>> indices;

    dinic(int s) : sz(s), g(sz), level(sz), startEdge(sz), indices(sz, vector<int>(sz, -1)) {}

    void addEdge(int from, int to, flowT capacity)
    {
        if (indices[from][to] != -1)
            changeCapacity(from, to, capacity);
        else
        {
            indices[from][to] = flow.size();
            g[from].push_back({to, (int) flow.size()});
            capacities.push_back(capacity), flow.push_back(0);
            indices[to][from] = flow.size();
            g[to].push_back({from, (int) flow.size()});
            capacities.push_back(0), flow.push_back(0);
        }
    }

    void changeCapacity(int from, int to, flowT delta)
    {
        capacities[indices[from][to]] += delta;
    }

    flowT residual(int id){return capacities[id] - flow[id];}

    bool buildLevelGraph(int source, int sink)
    {
        queue <int> q;
        q.push(source);
        fill(level.begin(), level.end(), -1);
        level[source] = 0;
        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            for (edge e: g[curr]) if (level[e.to] == -1 and residual(e.id) > 0)
            {
                q.push(e.to);
                level[e.to] = level[curr] + 1;
            }
        }
        return level[sink] != -1;
    }

    flowT blockingFlow(int curr, int sink, flowT sent = INF)
    {
        if (curr == sink) return sent;
        for (; startEdge[curr] < g[curr].size(); startEdge[curr]++)
        {
            edge e = g[curr][startEdge[curr]];
            if (level[e.to] == level[curr] + 1 and residual(e.id) > 0)
            {
                flowT augment = blockingFlow(e.to, sink, min(sent, residual(e.id)));
                if (augment > 0)
                {
                    flow[e.id] += augment;
                    flow[e.id ^ 1] -= augment;
                    return augment;
                }
            }
        }
        return 0;
    }

    flowT maxflow(int source, int sink)
    {
        flowT res = 0;
        while (buildLevelGraph(source, sink))
        {
            fill(startEdge.begin(), startEdge.end(), 0);
            while (flowT delta = blockingFlow(source, sink)) res += delta;
        }
        return res;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, p, k;
    cin >> n >> p >> k;

    int source = 0, sink = 1;
    dinic dnc(n);
    for (int i = 0; i < p; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b;
        dnc.addEdge(a, b, c);
        dnc.addEdge(b, a, c);
    }
    vector <int> flows = {dnc.maxflow(source, sink)};
    for (int i = 0; i < k; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b;
        bool changed = dnc.indices[a][b] == -1 or !dnc.residual(dnc.indices[a][b]) or !dnc.residual(dnc.indices[b][a]);
        dnc.addEdge(a, b, c);
        dnc.addEdge(b, a, c);
        if (changed)
            flows.push_back(flows.back() + dnc.maxflow(source, sink));
        else
            flows.push_back(flows.back());
    }
    for (auto f: flows)
        cout << f << '\n';
}
