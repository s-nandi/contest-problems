//dfs (flood fill)
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&page=show_problem&problem=5973
//2016 Mid-Atlantic Regional

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int n, m;
char grid[51][51];
bool visited[51][51];

vector <int> dx = {0, -1, 0, 1};
vector <int> dy = {-1, 0, 1, 0};

void dfs(int x, int y)
{
    if (!visited[x][y])
    {
        grid[x][y] = 'L';
        visited[x][y] = true;

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 and nx < n and ny >= 0 and ny < m and grid[nx][ny] != 'W')
            {
                dfs(nx, ny);
            }
        }
    }
}

int main()
{
    while (cin >> n >> m)
    {
        memset(visited, false, sizeof(visited));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin>>grid[i][j];
            }
        }

        int sol = 0;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == 'L' and !visited[i][j])
                {
                    dfs(i, j);
                    sol++;
                }
            }
        }

        cout<<sol<<'\n';
    }

    return 0;
}
