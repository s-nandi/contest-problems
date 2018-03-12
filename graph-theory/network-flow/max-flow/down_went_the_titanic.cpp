//network flow (edmond-karp, space-efficient representation, vertex capacities)
//https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2375

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1231231234;
const vector <int> dx = {-1, 0, 1, 0};
const vector <int> dy = {0, -1, 0, 1};

struct edge
{
    int to, id;
};

typedef vector<vector<edge>> graph;

vector <int> residual;
void addEdge(graph &g, int from, int to, int capacity)
{
    g[from].push_back({to, (int) residual.size()});
    residual.push_back(capacity);
    g[to].push_back({from, (int) residual.size()});
    residual.push_back(0);
}

int bfs(graph &g, int source, int sink)
{
    queue <int> q;
    vector <int> anc(g.size(), -1), ancId(g.size());
    q.push(source);

    bool reached = false;
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        if (curr == sink) {reached = true; break;}
        for (edge e: g[curr]) if (anc[e.to] == -1 and residual[e.id] > 0)
        {
            q.push(e.to);
            anc[e.to] = curr, ancId[e.to] = e.id;
        }
    }
    if (!reached) return 0;

    int augment = INF;
    for (int i = sink; i != source; i = anc[i])
    {
        int id = ancId[i];
        augment = min(augment, residual[id]);
    }

    for (int i = sink; i != source; i = anc[i])
    {
        int id = ancId[i];
        residual[id] -= augment;
        residual[id ^ 1] += augment;
    }

    return augment;
}

int edmondkarp(graph &g, int source, int sink)
{
    int res = 0;
    while (true)
    {
        int delta = bfs(g, source, sink);
        if (delta == 0) break;
        res += delta;
    }
    return res;
}

int mapping(int i, int j, int Y, bool outEdge)
{
    return 2 * (i * Y + j) + outEdge;
}

int main()
{
    int X, Y, P;
    while (cin>>X>>Y>>P)
    {
        char grid[X][Y];
        for (int i = 0; i < X; i++)
        {
            for (int j = 0; j < Y; j++)
            {
                cin>>grid[i][j];
            }
        }

        graph g(2 * X * Y + 2);
        int s = 2 * X * Y, t = 2 * X * Y + 1;

        for (int i = 0; i < X; i++)
        {
            for (int j = 0; j < Y; j++)
            {
                if (grid[i][j] == '~') continue;

                int currIn = mapping(i, j, Y, false);
                int currOut = mapping(i, j, Y, true);

                if(grid[i][j] == '.' or grid[i][j] == '*')
                {
                    addEdge(g, currIn, currOut, 1);
                    if (grid[i][j] == '*') addEdge(g, s, currIn, 1);
                }
                else
                {
                    addEdge(g, currIn, currOut, INF);
                    if (grid[i][j] == '#') addEdge(g, currOut, t, P);
                }

                for (int k = 0; k < 4; k++)
                {
                    int nx = i + dx[k];
                    int ny = j + dy[k];
                    if (nx >= 0 and nx < X and ny >= 0 and ny < Y)
                    {
                        if (grid[nx][ny] == '~') continue;
                        int neighborIn = mapping(nx, ny, Y, false);
                        addEdge(g, currOut, neighborIn, INF);
                    }
                }
            }
        }
        cout<<edmondkarp(g, s, t)<<endl;
    }

    return 0;
}
