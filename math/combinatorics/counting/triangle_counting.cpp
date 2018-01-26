//combinatorics (counting dp)
//https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2396

#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define MAXN 1000002

int main()
{
    vector <ll> newTriangles(MAXN);
    vector <ll> dp(MAXN);

    for (int i = 3; i < MAXN; i++)
    {
        newTriangles[i] = newTriangles[i - 2] + i - 3;
        dp[i] = newTriangles[i] + dp[i - 1];
    }

    int n;
    while(cin >> n)
    {
        if (n < 3) break;

        cout<<dp[n]<<'\n';
    }

    return 0;
}
