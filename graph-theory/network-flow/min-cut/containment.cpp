// max-flow min-cut (chepeast way to cut off defective nodes in graph - connect source to defective w/ INF weight)
// http://codeforces.com/gym/100827
// 2014 Pacific Northwest

#include <iostream>
#include <vector>

using namespace std;

const int INF = 1231231234;
const int MAXN = 10;

struct edge{int to, id;};
typedef vector<vector<edge>> graph;
typedef int flowT;

vector <int> dx = {0, -1, 0, 1, 0, 0};
vector <int> dy = {-1, 0, 1, 0, 0, 0};
vector <int> dz = {0, 0, 0, 0, -1, 1};

bool inBounds(int x, int y, int z)
{
    return x >= 0 and y >= 0 and z >= 0 and x < MAXN and y < MAXN and z < MAXN;
}

int position(int x, int y, int z)
{
    return MAXN * MAXN * x + MAXN * y + z;
}

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

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--)
    {
        int n;
        cin>>n;

        int sz = MAXN * MAXN * MAXN + 2;
        fordfulkerson ffa(sz);
        int source = sz - 2, sink = sz - 1;
        for (int i = 0; i < MAXN; i++)
        {
            for (int j = 0; j < MAXN; j++)
            {
                for (int k = 0; k < MAXN; k++)
                {
                    int pos = position(i, j, k);
                    for (int dir = 0; dir < 6; dir++)
                    {
                        int nx = i + dx[dir], ny = j + dy[dir], nz = k + dz[dir];
                        if (!inBounds(nx, ny, nz))
                            ffa.addEdge(pos, sink, 1);
                        else
                        {
                            int neighbor = position(nx, ny, nz);
                            ffa.addEdge(pos, neighbor, 1);
                        }
                    }
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            int x, y, z;
            cin>>x>>y>>z;
            int pos = position(x, y, z);
            ffa.addEdge(source, pos, INF);
        }
        cout << ffa.maxflow(source, sink) << '\n';
    }

    return 0;
}
