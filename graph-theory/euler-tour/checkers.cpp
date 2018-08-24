// detecting undirected euler tour (starting from specific node), exploiting parity on grid
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=5400
// 2015 Pacific Northwest Regional

#include <bits/stdc++.h>

using namespace std;

vector <int> dx = {-1, -1, 1, 1};
vector <int> dy = {-1, 1, 1, -1};

struct edge {int to, id;};
typedef vector <vector<edge>> graph;

const int MAXN = 26;
char grid[MAXN + 5][MAXN + 5];

struct eulerTour
{
    int n, m = 0, root = -1;
    graph g;
    bool isFeasible;
    vector <bool> used;
    deque <int> tour;

    eulerTour(graph &gr, int start)
    {
        g = gr, n = g.size();
        if (isFeasible = feasible(start))
        {
            getEdge(), used.resize(m);
            dfs(root), isFeasible = tour.size() == m + 1;
        }
    }

    void getEdge()
    {
        for (int i = 0; i < n; i++)
            m += g[i].size();
        m /= 2;
    }

    bool feasible(int start)
    {
        int numOdd = 0;
        vector <int> odds;
        for (int i = 0; i < n; i++) if (g[i].size())
        {
            if (g[i].size() & 1)
            {
                if (++numOdd > 2)
                    return false;
                odds.push_back(i);
            }
        }
        root = start;
        switch (numOdd)
        {
            case 0: return true;
            case 1: return false;
            case 2:
                return odds[0] == start or odds[1] == start;
        }
        throw "???";
    }

    void dfs(int curr)
    {
        for (edge e: g[curr]) if (!used[e.id])
        {
            used[e.id] = true;
            dfs(e.to);
        }
        tour.push_front(curr);
    }
};

int N;
bool inBounds(int x, int y)
{
    return x >= 0 and y >= 0 and x < N and y < N;
}

int position(int x, int y)
{
    return x * N + y;
}

int numEdges;
vector <int> visited;
set <pair<int, int>> created;
void dfs(graph &g, int x, int y)
{
    if (visited[position(x, y)])
        return;
    visited[position(x, y)] = true;

    for (int k = 0; k < 4; k++)
    {
        int nx = x + dx[k], ny = y + dy[k];
        int rx = nx + dx[k], ry = ny + dy[k];

        if (!inBounds(rx, ry))
            continue;
        if (grid[nx][ny] != 'W' or grid[rx][ry] != '_')
            continue;

        int from = position(x, y);
        int to = position(rx, ry);
        if (!created.count({from, to}))
        {
            g[from].push_back({to, numEdges});
            g[to].push_back({from, numEdges});
            created.insert({from, to}), created.insert({to, from});
            numEdges++;
        }
        if (!visited[position(rx, ry)])
            dfs(g, rx, ry);
    }
}

graph buildGraph(int sx, int sy)
{
    graph g(N * N);
    visited = vector<int>(N * N), created.clear();
    numEdges = 0;
    dfs(g, sx, sy);
    return g;
}

bool jumpAll(int sx, int sy, int numWhite)
{
    graph g = buildGraph(sx, sy);
    eulerTour eu(g, position(sx, sy));
    return eu.tour.size() == numWhite + 1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while (cin >> N)
    {
        int numWhite = 0;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> grid[i][j];
                numWhite += grid[i][j] == 'W';
            }
        }
        int numPossible = 0;
        pair <int, int> sol;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (grid[i][j] != 'B')
                    continue;
                if (jumpAll(i, j, numWhite))
                    numPossible++, sol = {i, j};
            }
        }

        if (numPossible == 0)
            cout<<"None"<<'\n';
        else if(numPossible > 1)
            cout<<"Multiple"<<'\n';
        else
        {
            int row = N - sol.first;
            char col = 'a' + sol.second;
            cout<<col<<row<<'\n';
        }
    }
    return 0;
}
