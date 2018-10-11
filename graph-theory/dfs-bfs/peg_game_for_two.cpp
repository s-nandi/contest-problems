// backtracking (why does this run quickly), hexagonal grid
// https://open.kattis.com/problems/peggamefortwo

#include <bits/stdc++.h>

using namespace std;

const int INF = 1231231234;
const int MAXN = 5;

vector <int> dx = {0, -1, -1, 0, 1, 1};
vector <int> dy = {-1, -1, 0, 1, 1, 0};

int n;
bool inBounds(int i, int j)
{
    return i >= 0 and j >= 0 and i < n and j <= i;
}

int grid[MAXN + 5][MAXN + 5];
int bestScore()
{
    int best = -INF;
    bool haveMove = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++) if (grid[i][j] > 0)
        {
            for (int k = 0; k < dx.size(); k++)
            {
                int nx = i + dx[k], ny = j + dy[k];
                int rx = i + 2 * dx[k], ry = j + 2 * dy[k];
                if (!inBounds(rx, ry) or grid[nx][ny] <= 0 or grid[rx][ry] != 0)
                    continue;

                int old_curr = grid[i][j], old_next = grid[nx][ny], old_res = grid[rx][ry];
                haveMove = true;

                int gain = grid[i][j] * grid[nx][ny];
                grid[i][j] = grid[nx][ny] = 0;
                grid[rx][ry] = old_curr;

                int loss = bestScore();
                int possible = gain - loss;

                best = max(best, possible);

                tie(grid[i][j], grid[nx][ny], grid[rx][ry]) = make_tuple(old_curr, old_next, old_res);
            }
        }
    }
    return haveMove ? best : 0;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    n = 5;
    memset(grid, -1, sizeof grid);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            cin >> grid[i][j];
        }
    }

    cout << bestScore() << '\n';
}
