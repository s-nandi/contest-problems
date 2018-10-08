// maximal bipartite matching (feasibility of placing unique number in each row/col, recovering solution)
// https://open.kattis.com/problems/superdoku
// 2018 North American Qualifier

#include <bits/stdc++.h>

using namespace std;

const int INF = 1231231234;
const int MAXN = 100;

typedef pair<int, int> ii;

struct edge{int to, id;};
typedef vector<vector<edge>> graph;
typedef int flowT;

struct fordfulkerson
{
    int sz;
    graph g;
    vector <vector<int>> table;

    vector <flowT> capacities, flow;
    vector <int> visited;

    fordfulkerson(int s)
    {
        sz = s, g.resize(sz);
        visited.resize(sz);
        table.resize(sz, vector<int>(sz));
    }

    void addEdge(int from, int to, flowT capacity)
    {
        table[from][to] = flow.size();
        g[from].push_back({to, (int) flow.size()});
        capacities.push_back(capacity), flow.push_back(0);

        table[to][from] = flow.size();
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
        fill(flow.begin(), flow.end(), 0);
        while(delta = dfs(source, sink))
        {
            res += delta;
            fill(visited.begin(), visited.end(), 0);
        }
        return res;
    }

    void recover(int source, int sink, int curr, vector <ii> &sol)
    {
        for (edge e: g[curr]) if (flow[e.id] > 0)
        {
            if (curr != source and e.to != sink)
            {
                sol.push_back({curr, e.to});
                --capacities[e.id];
            }
            recover(source, sink, e.to, sol);
        }
    }
};

int grid[MAXN + 5][MAXN + 5];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    int sz = 2 * n + 2;
    int source = sz - 2, sink = sz - 1;
    fordfulkerson ffa(sz);

    for (int i = 0; i < n; i++)
    {
        ffa.addEdge(source, i, 1);
        for (int j = 0; j < n; j++)
            ffa.addEdge(i, j + n, 1);
        ffa.addEdge(i + n, sink, 1);
    }

    bool feasible = true;
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> grid[i][j];
            --grid[i][j];

            int from = grid[i][j], to = j + n;
            if (--ffa.capacities[ffa.table[from][to]] < 0)
                feasible = false;
        }
    }

    if (feasible)
    {
        for (int i = k; i < n; i++)
        {
            int possible = ffa.maxflow(source, sink);
            if (possible < n)
            {
                feasible = false;
                break;
            }
            else
            {
                vector <ii> sol;
                ffa.recover(source, sink, source, sol);
                for (auto elem: sol)
                    grid[i][elem.second - n] = elem.first;
            }
        }
    }

    if (feasible)
    {
        cout << "yes" << '\n';
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << grid[i][j] + 1 << " ";
            }
            cout << '\n';
        }
    }
    else
        cout << "no" << '\n';
}
