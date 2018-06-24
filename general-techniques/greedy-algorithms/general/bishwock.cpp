//greedy (placing objects on grid)
//http://codeforces.com/contest/991/problem/D

#include <iostream>
#include <vector>

using namespace std;

int n;
char grid[2][101];

bool hasSpace(int l, int r)
{
    int numEmpty = 0;
    l = max(0, l);
    r = min(r, n - 1);
    for (int i = 0; i < 2; i++)
    {
        for (int j = l; j <= r; j++)
        {
            if (grid[i][j] == '0')
            {
                numEmpty++;
            }
        }
    }
    return numEmpty >= 3;
}

void fillup(int l, int r)
{
    int numFilled = 0;
    l = max(0, l);
    r = min(r, n - 1);
    for (int i = 0; i < 2; i++)
    {
        for (int j = l; j <= r; j++)
        {
            if (grid[i][j] == '0' and numFilled < 3)
            {
                grid[i][j] = 'X';
                numFilled++;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, t;
    cin>>s>>t;

    n = s.length();

    vector <pair<int, int>> blocked;
    for (int i = 0; i < n; i++)
    {
        grid[0][i] = s[i];
        if (s[i] == 'X')
        {
            blocked.push_back({0, i});
        }

    }
    for (int i = 0; i < n; i++)
    {
        grid[1][i] = t[i];
        if (t[i] == 'X')
        {
            blocked.push_back({1, i});
        }
    }

    int sol = 0;
    for (auto block: blocked)
    {
        if (hasSpace(block.first - 1, block.first))
        {
            fillup(block.first - 1, block.first);
            sol++;
        }
        else if(hasSpace(block.first, block.first + 1))
        {
            fillup(block.first, block.first + 1);
            sol++;
        }
    }
    for (int i = 0; i < n - 1; i++)
    {
        if (hasSpace(i, i + 1))
        {
            fillup(i, i + 1);
            sol++;
        }
    }
    cout<<sol<<'\n';

    return 0;
}
