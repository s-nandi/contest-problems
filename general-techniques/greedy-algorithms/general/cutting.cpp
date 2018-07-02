//greedy (reducing cases)
//https://codeforces.com/contest/998/problem/B

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, b;
    cin>>n>>b;

    vector <int> a(n), cuts;
    int neven = 0, nodd = 0;
    for (int i = 0; i < n; i++)
    {
        cin>>a[i];

        if (a[i] & 1) nodd++;
        else neven++;

        if (nodd == neven and i != n - 1)
        {
            cuts.push_back(i);
        }
    }

    vector <int> costs;
    for (int cut: cuts)
    {
        int cost = abs(a[cut] - a[cut + 1]);
        costs.push_back(cost);
    }

    sort(costs.begin(), costs.end());

    int it = 0, used = 0;
    while (it < costs.size() and b - used >= costs[it])
    {
        used += costs[it];
        it++;
    }
    cout<<it<<'\n';

    return 0;
}
