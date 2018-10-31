// min cost max flow (undirected edges)
// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1535

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = numeric_limits<ll>::max() / 4;

struct edge{int to, id;};
typedef vector<vector<edge>> graph;

typedef ll flowT;
typedef ll costT;
struct minCostMaxFlow
{
    int sz;
    graph g;
    vector <flowT> capacities, flow, sent;
    vector <costT> costs, distances;
    vector <int> prev, pid, inq;

    minCostMaxFlow(int s) : sz(s), g(sz), sent(sz), distances(sz), prev(sz), pid(sz), inq(sz) {}

    void addEdge(int from, int to, flowT capacity, costT cost)
    {
        g[from].push_back({to, (int) flow.size()});
        capacities.push_back(capacity), flow.push_back(0), costs.push_back(cost);
        g[to].push_back({from, (int) flow.size()});
        capacities.push_back(0), flow.push_back(0), costs.push_back(-cost);
    }

    flowT residual(int id){return capacities[id] - flow[id];}

    ll spfa(int s, int t)
    {
        fill(sent.begin(), sent.end(), INF);
        fill(distances.begin(), distances.end(), INF);
        fill(inq.begin(), inq.end(), 0);

        queue <int> q;
        q.push(s);
        distances[s] = 0, inq[s] = true;
        while (!q.empty())
        {
            int curr = q.front();
            q.pop();

            inq[curr] = false;
            for (edge e: g[curr]) if (residual(e.id) > 0 and distances[curr] + costs[e.id] < distances[e.to])
            {
                distances[e.to] = distances[curr] + costs[e.id];
                prev[e.to] = curr, pid[e.to] = e.id;
                sent[e.to] = min(sent[curr], residual(e.id));
                if (!inq[e.to])
                    q.push(e.to), inq[e.to] = true;
            }
        }
        return distances[t] < INF ? sent[t] : 0;
    }

    pair <flowT, costT> maxflow(int source, int sink, flowT target = INF)
    {
        flowT f = 0, delta;
        costT cost = 0;
        while(delta = spfa(source, sink))
        {
            delta = min(delta, target - f);
            f += delta;
            for (int i = sink; i != source; i = prev[i])
            {
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

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    while (cin >> n >> m)
    {
        vector <pair <int, int>> edges(m);
        vector <int> costs(m);
        for (int i = 0; i < m; i++)
        {
            int a, b, c;
            cin >> a >> b >> c;
            edges[i] = {--a, --b};
            costs[i] = c;
        }
        int d, k;
        cin >> d >> k;

        int source = n, sink = n + 1;
        minCostMaxFlow mcmf(n + 2);
        for (int i = 0; i < m; i++)
        {
            mcmf.addEdge(edges[i].first, edges[i].second, k, costs[i]);
            mcmf.addEdge(edges[i].second, edges[i].first, k, costs[i]);
        }
        mcmf.addEdge(source, 0, INF, 0), mcmf.addEdge(n - 1, sink, INF, 0);

        auto res = mcmf.maxflow(source, sink, d);
        if (res.first < d)
            cout << "Impossible." << '\n';
        else
            cout << res.second << '\n';
    }
}
