// Erdos–Szekeres theorem (rs + 1 long sequence must have r+1 length LIS or s+1 length LDS)
// https://codeforces.com/contest/1017/problem/C

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int INF = 1231231234;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    vector <int> sol(n);
    // If we limit length of lis at r, then by erdo-szekeres theorem ->
    // we know n = rs + 1 long sequence must have s = (n - 1) / r + 1 long LDS since lis is less than r + 1
    int best = INF, bestLis = -1;
    for (int lis = 1; lis <= n; lis++)
    {
        int lds = (n - 1) / lis + 1;
        if (lds + lis < best)
        {
            best = lds + lis;
            bestLis = lis;
        }
    }

    int it = bestLis, increasing = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        sol[i] = it;
        increasing++;
        --it;
        if (increasing == bestLis)
            it = min(it + 2 * bestLis, n), increasing = 0;
    }

    for (int i: sol)
        cout<<i<<" ";
    cout<<'\n';

    return 0;
}
