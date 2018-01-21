//bitmasks, dynamic programming, greedy
//http://codeforces.com/contest/913/problem/C

#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define INF (ll) 1e18

int main()
{
    int n, l;
    cin>>n>>l;

    vector <ll> costs(n);

    for (int i = 0; i < n; i++)
    {
        cin>>costs[i];
        if (i > 0)
            costs[i] = min(costs[i], 2 * costs[i - 1]);
    }

    vector <ll> match(n + 1);
    vector <int> numBits(n);

    match[n] = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        numBits[i] = l / (1 << i);
        match[i] = match[i + 1] + costs[i] * numBits[i];
        l -= numBits[i] * (1 << i);
    }

    ll bestCost = match[0];
    for (int i = 0; i < n; i++)
    {
        ll potential = (numBits[i] + 1) * costs[i] + match[i + 1];
        bestCost = min(bestCost, potential);
    }

    cout<<bestCost<<'\n';

    return 0;
}
