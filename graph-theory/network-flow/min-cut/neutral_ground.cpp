// min-cut (vertex capacities, disconnect two sets)
// https://open.kattis.com/problems/neutralground
// 2018 Mid-Atlantic Regional

#include <bits/stdc++.h>

using namespace std;

const int INF = 1231231234;
const int MAXN = 45;

vector <int> dx = {0, -1, 0, 1};
vector <int> dy = {-1, 0, 1, 0};

struct edge{int to, id;};
typedef vector<vector<edge>> graph;
typedef int flowT;

struct fordfulkerson
{
    int sz;
    graph g;
    vector <flowT> capacities, flow;
    vector <int> visited;

    fordfulkerson(int s) : sz(s), g(sz), visited(sz) {}

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

int n, m;
int mapping(int i, int j, bool in)
{
    return 2 * (i * m + j) + in;
}

bool inBounds(int i, int j)
{
    return i >= 0 and j >= 0 and i < n and j < m;
}

char grid[MAXN][MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> m >> n;

    int sz = 2 * n * m + 2;
    int source = sz - 2, sink = sz - 1;

    fordfulkerson ffa(sz);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> grid[i][j];

            if (grid[i][j] == 'A' or grid[i][j] == 'B')
                ffa.addEdge(mapping(i, j, true), mapping(i, j, false), INF);
            else
                ffa.addEdge(mapping(i, j, true), mapping(i, j, false), grid[i][j] - '0');

            if (grid[i][j] == 'A')
                ffa.addEdge(source, mapping(i, j, true), INF);
            else if (grid[i][j] == 'B')
                ffa.addEdge(mapping(i, j, false), sink, INF);
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                int nx = i + dx[k], ny = j + dy[k];
                if (!inBounds(nx, ny))
                    continue;
                ffa.addEdge(mapping(i, j, false), mapping(nx, ny, true), INF);
            }
        }
    }
    cout << ffa.maxflow(source, sink) << '\n';
}
