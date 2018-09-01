// maintaining bracketed ranges
// http://codeforces.com/contest/1028/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int INF = 1231231234;
const int MOD = 1000000007;

int mult(int a, int b)
{
    return (ll) a * b % MOD;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>>n;

    int highestBuy = -INF, lowestSell = INF;
    set <int> orders = {-INF, INF};
    int sol = 1;
    for (int i = 0; i < n; i++)
    {
        string command; int v;
        cin>>command>>v;

        if (command[1] == 'D')
        {
            orders.insert(v);
        }
        else
        {
            if (v > lowestSell or v < highestBuy)
            {
                sol = 0;
                break;
            }
            if (v < lowestSell and v > highestBuy)
            {
                sol = mult(2, sol);
            }
            auto it = orders.find(v);
            lowestSell = *next(it);
            highestBuy = *prev(it);

            orders.erase(it);
        }
    }
    int remaining = 0;
    for (int i: orders)
    {
        if (i < lowestSell and i > highestBuy)
            remaining++;
    }
    sol = mult(sol, remaining + 1);
    cout<<sol<<'\n';

    return 0;
}
