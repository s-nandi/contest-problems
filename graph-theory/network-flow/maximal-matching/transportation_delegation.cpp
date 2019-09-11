// max flow (maximal matching)
// https://open.kattis.com/problems/transportation
// 2015 East-Central NA Regional

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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

    dinic(int s)
    {
        sz = s, g.resize(sz);
        level.resize(sz), startEdge.resize(sz);
    }

    void addEdge(int from, int to, flowT capacity)
    {
        g[from].push_back({to, (int) flow.size()});
        capacities.push_back(capacity), flow.push_back(0);
        g[to].push_back({from, (int) flow.size()});
        capacities.push_back(0), flow.push_back(0);
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

template <typename T> bool contains(vector <T> &sorted, T i)
{
    return binary_search(sorted.begin(), sorted.end(), i);
}

int numString = 0;
map <string, int> mapping;
int getIndex(const string &s)
{
    if (!mapping.count(s))
    {
        mapping[s] = numString++;
        return numString - 1;
    }
    else return mapping[s];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int s, r, f, t;
    cin >> s >> r >> f >> t;

    vector <int> raw(r), factory(f);
    for (auto &elem: raw)
    {
        string str;
        cin >> str;
        elem = getIndex(str);
    }
    for (auto &elem: factory)
    {
        string str;
        cin >> str;
        elem = getIndex(str);
    }

    vector <vector<int>> transport(t);
    for (auto &elem: transport)
    {
        int sz;
        cin >> sz;
        elem.resize(sz);
        for (auto &e: elem)
        {
            string str;
            cin >> str;
            e = getIndex(str);
        }
        sort(elem.begin(), elem.end());
    }

    int sz = r + f + 2 * t + 2;
    int source = sz - 2, sink = sz - 1;
    dinic dnc(sz);
    for (int i = 0; i < r; i++)
    {
        dnc.addEdge(source, i, 1);
    }
    for (int i = 0; i < f; i++)
    {
        dnc.addEdge(r + i, sink, 1);
    }
    for (int i = 0; i < t; i++)
    {
        dnc.addEdge(r + f + i, r + f + i + t, 1);
    }
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < t; j++)
        {
            if (contains(transport[j], raw[i]))
            {
                dnc.addEdge(i, r + f + j, 1);
            }
        }
    }
    for (int i = 0; i < f; i++)
    {
        for (int j = 0; j < t; j++)
        {
            if (contains(transport[j], factory[i]))
            {
                dnc.addEdge(r + f + t + j, r + i, 1);
            }
        }
    }
    for (int i = 0; i < t; i++)
    {
        for (int j = i + 1; j < t; j++)
        {
            bool overlap = false;
            for (auto state: transport[i])
            {
                if (contains(transport[j], state))
                {
                    overlap = true;
                    break;
                }
            }
            if (overlap)
            {
                dnc.addEdge(r + f + t + i, r + f + j, 1);
                dnc.addEdge(r + f + t + j, r + f + i, 1);
            }
        }
    }
    cout << dnc.maxflow(source, sink) << '\n';
}
