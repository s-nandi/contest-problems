// dfs (flood fill)
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=762
// 2016 East Central Regional

#include <bits/stdc++.h>

using namespace std;

vector <int> dx = {0, -1, 0, 1};
vector <int> dy = {-1, 0, 1, 0};

const int MAXN = 100;

int n, m;
bool inBounds(int i, int j)
{
    return i >= 0 and j >= 0 and i < n and j < m;
}

bool onBoundary(int i, int j)
{
    return i == 0 or j == 0 or i == n - 1 or j == m - 1;
}

char grid[MAXN + 5][MAXN + 5];
bool isIntersection(int i, int j)
{
    for (int k = 0; k < 4; k++)
    {
        int nx = i + dx[k], ny = j + dy[k];
        if (!inBounds(nx, ny) or grid[nx][ny] == '.')
            return false;
    }
    return true;
}

bool boundary[MAXN + 5][MAXN + 5][2];
void calculateBoundary(int i, int j, int ch, int prev = -1)
{
    if (boundary[i][j][ch])
        return;

    boundary[i][j][ch] = 1;
    bool crossing = isIntersection(i, j);

    for (int k = 0; k < 4; k++)
    {
        if (crossing and k != prev)
            continue;

        int nx = i + dx[k], ny = j + dy[k];
        if (!inBounds(nx, ny) or grid[nx][ny] == '.')
            continue;

        calculateBoundary(nx, ny, ch, k);
    }
}

int outside[MAXN + 5][MAXN + 5][2];
void connectToExterior(int i, int j, int ch)
{
    if (outside[i][j][ch])
        return;
    outside[i][j][ch] = 1;

    for (int k = 0; k < 4; k++)
    {
        int nx = i + dx[k], ny = j + dy[k];

        if (!inBounds(nx, ny) or boundary[nx][ny][ch])
            continue;
        connectToExterior(nx, ny, ch);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while (cin >> n >> m)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin>>grid[i][j];
            }
        }

        memset(boundary, 0, sizeof(boundary));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == 'A' or grid[i][j] == 'B')
                    calculateBoundary(i, j, grid[i][j] - 'A');
            }
        }

        memset(outside, 0, sizeof(outside));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++) if (onBoundary(i, j))
            {
                for (int t = 0; t < 2; t++)
                {
                    if (grid[i][j] == '.' and !outside[i][j][t])
                        connectToExterior(i, j, t);
                }
            }
        }

        int sumA = 0, sumB = 0, sumI = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] != '.')
                    continue;
                if (!outside[i][j][0] and !outside[i][j][1])
                    sumI++;
                else if(!outside[i][j][0])
                    sumA++;
                else if(!outside[i][j][1])
                    sumB++;
            }
        }
        cout<<sumA<<" "<<sumB<<" "<<sumI<<'\n';
    }

    return 0;
}
