//greedy (grid assignment)
//https://open.kattis.com/problems/recovery

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    string s, t;
    cin>>s>>t;
    int n = s.length(), m = t.length();

    vector <int> r(n), c(m);
    for (int i = 0; i < n; i++) r[i] = s[i] - '0';
    for (int i = 0; i < m; i++) c[i] = t[i] - '0';

    vector <vector<int>> grid(n, vector<int>(m, 1));
    vector <int> wr(n), wc(m);
    int wrongRows = 0, wrongCols = 0;

    for (int i = 0; i < n; i++)
    {
        wr[i] = (m & 1) ^ r[i];
        wrongRows += wr[i];
    }

    for (int i = 0; i < m; i++)
    {
        wc[i] = (n & 1) ^ c[i];
        wrongCols += wc[i];
    }

    int diff = abs(wrongCols - wrongRows);
    if (diff & 1)
    {
        cout<<-1<<'\n';
        return 0;
    }

    if (wrongRows > wrongCols)
    {
        for (int i = 0, d = 0; d < diff; i++) if (wr[i])
        {
            grid[i][0] = 0;
            wr[i] = 0;
            d++;
        }
    }
    else
    {
        for (int i = 0, d = 0; d < diff; i++) if (wc[i])
        {
            grid[0][i] = 0;
            wc[i] = 0;
            d++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (wr[i] & wc[j])
            {
                grid[i][j] = 0;
                wr[i] = 0, wc[j] = 0;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout<<grid[i][j];
        }
        cout<<'\n';
    }

    return 0;
}
