//network flow (edmond-karp, maximum independent set on bipartite), dfs (flood fill)
//http://codeforces.com/gym/101201/attachments
//2016 Pacific Northwest Regional

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

#define INF 123123123
#define MAXN 2000

int n, m;

char grid[41][41];
vector <int> dx = {0, -1, 0, 1};
vector <int> dy = {-1, 0, 1, 0};

vector <vector<int>> graph;
int residual[MAXN][MAXN];

int bfs(int source, int sink)
{
    queue <int> q;
    vector <int> anc(graph.size(), -1);
    q.push(source);

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

        for (int neighbor: graph[curr])
        {
            if (anc[neighbor] == -1 and residual[curr][neighbor] > 0)
            {
                q.push(neighbor);
                anc[neighbor] = curr;
            }
        }
    }

    if (!reached) return 0;

    int augment = INF;

    for (int node = sink; node != source; node = anc[node])
    {
        augment = min(augment, residual[anc[node]][node]);
    }

    for (int node = sink; node != source; node = anc[node])
    {
        residual[anc[node]][node] -= augment;
        residual[node][anc[node]] += augment;
    }

    return augment;
}

int edmondkarp(int source, int sink)
{
    int res = 0;
    while (true)
    {
        int delta = bfs(source, sink);
        if (delta == 0) break;
        res += delta;
    }
    return res;
}

bool valid(int i, int j)
{
    return (i >= 0 and j >= 0 and i < n and j < m);
}

void add_edge(int i, int j)
{
    graph[i].push_back(j); residual[i][j] = 1;
    graph[j].push_back(i); residual[j][i] = 0;
}

int mapping(int i, int j)
{
    return i * m + j;
}

int visited[41][41];

void floodfill(int x, int y)
{
    if (visited[x][y]) return;
    visited[x][y] = 1;

    for (int dir = 0; dir < 4; dir++)
    {
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if (valid(nx, ny))
        {
            if(grid[nx][ny] == 'L')
            {
                floodfill(nx, ny);
            }
            else if(grid[nx][ny] == 'C')
            {
                grid[nx][ny] = 'W';
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n>>m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin>>grid[i][j];
        }
    }

    memset(visited, 0, sizeof(visited));
    int preExisting = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 'L' and visited[i][j] == 0)
            {
                floodfill(i, j);
                preExisting++;
            }
        }
    }

    graph.resize(n * m + 2);
    int s = n * m;
    int t = n * m + 1;

    int numNodes = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] != 'C') continue;
            else numNodes++;

            int curr = mapping(i, j);
            vector <int> neighbors;

            for (int dir = 0; dir < 4; dir++)
            {
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                if (valid(nx, ny) and grid[nx][ny] == 'C')
                {
                    int neighbor = mapping(nx, ny);
                    neighbors.push_back(neighbor);
                }
            }

            if ((i + j) % 2 == 0)
            {
                add_edge(s, curr);
                for (int neighbor: neighbors)
                {
                    add_edge(curr, neighbor);
                }
            }
            else
            {
                for (int neighbor: neighbors)
                {
                    add_edge(neighbor, curr);
                }
                add_edge(curr, t);
            }
        }
    }

    cout<<preExisting + numNodes - edmondkarp(s, t)<<'\n';

    return 0;
}
