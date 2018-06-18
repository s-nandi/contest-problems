//sliding window, finding longest row/column of character in grid
//http://codeforces.com/contest/919/problem/C

#include <iostream>

using namespace std;


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin>>n>>m>>k;

    char grid[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin>>grid[i][j];
        }
    }

    int sol = 0, horiz = 0, vert = 0;
    for (int i = 0; i < n; i++)
    {
        int curr = 0;
        for (int j = 0; j < m; j++)
        {
            if (j > k - 1 and grid[i][j - k] == '.') curr--;
            if (grid[i][j] == '.') curr++;
            if (curr == k) horiz++;
        }
    }

    for (int j = 0; j < m; j++)
    {
        int curr = 0;
        for (int i = 0; i < n; i++)
        {
            if (i > k - 1 and grid[i - k][j] == '.') curr--;
            if (grid[i][j] == '.') curr++;
            if (curr == k) vert++;
        }
    }

    sol = horiz + vert;
    if (k == 1) sol /= 2;

    cout<<sol<<'\n';


    return 0;
}
