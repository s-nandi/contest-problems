// network flow (# of vertex disjoint paths on bipartite graph), blocked n-rooks problem, binary search
// https://open.kattis.com/problems/gridgame
// 2018 Singapore Preliminary

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 30;
int grid[MAXN][MAXN];

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
        visited.assign(sz, 0);
        while(delta = dfs(source, sink))
        {
            res += delta;
            fill(visited.begin(), visited.end(), 0);
        }
        return res;
    }
};

int n;
bool solvable(int v)
{
    int sz = 2 * n + 2;
    int source = sz - 2, sink = sz - 1;
    fordfulkerson ffa(sz);

    for (int i = 0; i < n; i++)
    {
        ffa.addEdge(source, 2 * i, 1);
        ffa.addEdge(2 * i + 1, sink, 1);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] >= v)
            {
                ffa.addEdge(2 * i, 2 * j + 1, 1);
            }
        }
    }
    return ffa.maxflow(source, sink) == n;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;

    int mv = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> grid[i][j];
            mv = max(mv, grid[i][j]);
        }
    }

    int l = 1, r = mv;
    while (l < r)
    {
        int m = (l + r + 1) / 2;

        if (solvable(m))
            l = m;
        else
            r = m - 1;
    }
    cout<<l<<'\n';
}
