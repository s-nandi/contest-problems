//simulation (circular rotations)
//https://codeforces.com/contest/996/problem/C

#include <iostream>
#include <vector>
#include <map>

using namespace std;

map <int, pair<int, int>> parking;
int grid[4][51];
int n;

pair <int, int> next(int i, int j)
{
    if (i == 1)
    {
        if (j == n - 1)
        {
            return {2, n - 1};
        }
        else
        {
            return {1, j + 1};
        }
    }
    else
    {
        if (j == 0)
        {
            return {1, 0};
        }
        else
        {
            return {2, j - 1};
        }
    }
}

bool neighbor(int x1, int y1, int x2, int y2)
{
    return (x1 == x2 and abs(y1 - y2) == 1) or (y1 == y2 and abs(x1 - x2) == 1);
}

bool parkable(int i, int x, int y)
{
    return neighbor(parking[i].first, parking[i].second, x, y);
}

struct command
{
    int i, r, c;
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int k;
    cin>>n>>k;

    vector <command> commands;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin>>grid[i][j];
            if ((i == 0 or i == 3) and grid[i][j] != 0)
            {
                parking[grid[i][j]] = {i, j};
            }
        }
    }

    int numParked = 0;
    for (int i = 1; i <= 2; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int car = grid[i][j];
            if (car != 0 and parkable(car, i, j))
            {
                commands.push_back({car, parking[car].first, parking[car].second});
                grid[parking[car].first][parking[car].second] = car;
                grid[i][j] = 0;
                numParked++;
            }
        }
    }

    if (k < 2 * n or numParked > 0)
    {
        while (numParked < k)
        {
            pair <int, int> emptySpot = {-1, -1};
            for (int i = 1; i <= 2; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (grid[i][j] == 0)
                    {
                        emptySpot = {i, j};
                        break;
                    }
                }
            }
            while (numParked < k)
            {
                pair <int, int> nextSpot = next(emptySpot.first, emptySpot.second);
                int car = grid[nextSpot.first][nextSpot.second];
                if (car != 0)
                {
                    if (parkable(car, nextSpot.first, nextSpot.second))
                    {
                        commands.push_back({car, parking[car].first, parking[car].second});
                        grid[parking[car].first][parking[car].second] = car;
                        numParked++;

                    }
                    else
                    {
                        commands.push_back({car, emptySpot.first, emptySpot.second});
                        grid[emptySpot.first][emptySpot.second] = car;
                    }
                }
                grid[nextSpot.first][nextSpot.second] = 0;
                emptySpot = nextSpot;
            }
        }

        cout<<commands.size()<<'\n';
        for (command c: commands)
        {
            cout<<c.i<<" "<<c.r + 1 <<" "<<c.c + 1<<'\n';
        }
    }
    else
    {
        cout<<-1<<'\n';
    }

    return 0;
}
