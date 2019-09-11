// network flow (ford-fulkerson, finding optimal matching)
// https://open.kattis.com/problems/waif
// 2016 East Central Regional

#include <bits/stdc++.h>

using namespace std;

const int INF = 1231231234;

struct edge{int to, id;};
typedef vector<vector<edge>> graph;
typedef int flowT;

struct fordfulkerson
{
    int sz;
    graph g;
    vector <flowT> capacities, flow;
    vector <int> visited;

    fordfulkerson(int s)
    {
        sz = s, g.resize(sz);
        visited.resize(sz);
    }

    void addEdge(int from, int to, flowT capacity)
    {
        g[from].push_back({to, (int) flow.size()});
        capacities.push_back(capacity), flow.push_back(0);
        g[to].push_back({from, (int) flow.size()});
        capacities.push_back(0), flow.push_back(0);
    }

    flowT residual(int id){return capacities[id] - flow[id];}

    int dfs(int curr, int sink, flowT sent = INF)
    {
        if (curr == sink)
            return sent;

        if(visited[curr])
            return 0;
        visited[curr] = true;

        for (edge e: g[curr]) if (residual(e.id) > 0)
        {
            flowT augment = dfs(e.to, sink, min(sent, residual(e.id)));
            if (augment > 0)
            {
                flow[e.id] += augment;
                flow[e.id ^ 1] -= augment;
                return augment;
            }
        }
        return 0;
    }

    flowT maxflow(int source, int sink)
    {
        flowT res = 0, delta;
        while (delta = dfs(source, sink))
        {
            res += delta;
            fill(visited.begin(), visited.end(), 0);
        }
        return res;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, p;
    while (cin >> n >> m >> p)
    {
        vector <vector<int>> children(n);
        for (int i = 0; i < n; i++)
        {
            int num;
            cin>>num;
            for (int j = 0; j < num; j++)
            {
                int x;
                cin>>x;
                children[i].push_back(--x);
            }
        }
        vector <int> category(m, -1);
        vector <int> limits(p);
        for (int i = 0; i < p; i++)
        {
            int num;
            cin>>num;
            for (int j = 0; j < num; j++)
            {
                int x;
                cin>>x;
                category[--x] = i;
            }
            cin >> limits[i];
        }

        int sz = n + m + p + 2;
        fordfulkerson ffa(sz);
        int source = sz - 2, sink = sz - 1;

        // Connect children to toys
        for (int i = 0; i < n; i++)
        {
            int child = i;
            ffa.addEdge(source, child, 1);
            for (int j: children[child])
            {
                int toy = j + n;
                ffa.addEdge(child, toy, 1);
            }
        }
        // Connect toys to category or sink (if no category)
        for (int i = 0; i < m; i++)
        {
            int toy = i + n;
            if (category[i] != -1)
            {
                int cat = category[i] + n + m;
                ffa.addEdge(toy, cat, 1);
            }
            else
            {
                ffa.addEdge(toy, sink, 1);
            }
        }
        // Connect categories to sink
        for (int i = 0; i < p; i++)
        {
            int cat = i + n + m;
            ffa.addEdge(cat, sink, limits[i]);
        }
        int flow = ffa.maxflow(source, sink);
        cout<<flow<<'\n';
    }

    return 0;
}
