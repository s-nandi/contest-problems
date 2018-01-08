//network flow (edmond-karp, space-efficient), vertex capacities
//https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2375

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define INF 1231231234

struct edge
{
    int i;
    int capacity;
    int flow;
    int residual()
    {
        return capacity - flow;
    }
};

struct ancestor
{
    int ancestorNode;
    int edgeIndex;
};

vector <edge> edges;
vector <vector<int>> graph;

vector <int> dx = {-1, 0, 1, 0};
vector <int> dy = {0, -1, 0, 1};

void addEdge(int from, int to, int capacity)
{
    graph[from].push_back(edges.size());
    edges.push_back({to, capacity, 0});
    graph[to].push_back(edges.size());
    edges.push_back({from, 0, 0});
}

int bfs(int source, int sink)
{
    queue <int> q;
    q.push(source);

    vector <ancestor> anc(graph.size(), {-1, -1});
    anc[source] = {-2, -1};

    bool reached = false;

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        if (curr == sink)
        {
            reached = true;
            break;
        }

        for (int index: graph[curr])
        {
            edge e = edges[index];
            int neighbor = e.i;
            if (anc[neighbor].ancestorNode == -1 and e.residual() > 0)
            {
                q.push(neighbor);
                anc[neighbor] = {curr, index};
            }
        }
    }

    if (!reached) return 0;

    int augment = INF;
    for (int i = sink; i != source; i = anc[i].ancestorNode)
    {
        int ind = anc[i].edgeIndex;
        augment = min(augment, edges[ind].residual());
    }

    for (int i = sink; i != source; i = anc[i].ancestorNode)
    {
        int ind = anc[i].edgeIndex;
        edges[ind].flow += augment;
        edges[ind ^ 1].flow -= augment;
    }

    return augment;
}

int edmondkarp(int source, int sink)
{
    int res = 0;
    while (true)
    {
        int delta = bfs(source, sink);
        if (delta == 0)
        {
            break;
        }
        res += delta;
    }

    return res;
}

int mapping(int i, int j, int Y, bool in)
{
    return 2 * (i * Y + j) + (in ? 0 : 1);
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

        int s = 2 * X * Y;
        int t = 2 * X * Y + 1;

        graph.clear();
        graph.resize(2 * X * Y + 2);

        for (int i = 0; i < X; i++)
        {
            for (int j = 0; j < Y; j++)
            {
                if (grid[i][j] == '~') continue;

                int currIn = mapping(i, j, Y, true);
                int currOut = mapping(i, j, Y, false);

                if(grid[i][j] == '.' or grid[i][j] == '*')
                {
                    addEdge(currIn, currOut, 1);
                }
                else
                {
                    addEdge(currIn, currOut, INF);
                }

                if (grid[i][j] == '*')
                {
                    addEdge(s, currIn, 1);
                }
                else if (grid[i][j] == '#')
                {
                    addEdge(currOut, t, P);
                }

                for (int dir = 0; dir < 4; dir++)
                {
                    int nx = i + dx[dir];
                    int ny = j + dy[dir];

                    if (nx >= 0 and nx < X and ny >= 0 and ny < Y)
                    {
                        if (grid[nx][ny] == '~') continue;

                        int neighborIn = mapping(nx, ny, Y, true);
                        addEdge(currOut, neighborIn, INF);
                    }
                }
            }
        }

        cout<<edmondkarp(s, t)<<endl;
    }

    return 0;
}
