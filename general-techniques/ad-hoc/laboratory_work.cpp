//ad-hoc (optimized replacements)
//http://codeforces.com/contest/931/problem/C

#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    map <int, int> counts;
    vector <int> a(n);

    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
        counts[a[i]]++;
    }

    if (counts.rbegin() -> first - counts.begin() -> first < 2)
    {
        cout<<n<<'\n';
        for (int i = 0; i < n; i++)
        {
            cout<<a[i]<<" ";
        }
    }
    else
    {
        int first = counts.begin() -> first;

        int minCost = n;
        int solType = 0;
        int solDiff = 0;

        for (int i = 1; counts[first] - i >= 0 and counts[first + 2] - i >= 0; i++)
        {
            int cost = counts[first] - i + counts[first + 1] + counts[first + 2] - i;
            if (cost < minCost)
            {
                minCost = cost;
                solDiff = i;
                solType = 0;
            }
        }

        for (int i = 1; counts[first + 1] - 2 * i >= 0; i++)
        {
            int cost = counts[first] + counts[first + 1] - 2 * i + counts[first + 2];
            if (cost < minCost)
            {
                minCost = cost;
                solDiff = i;
                solType = 1;
            }
        }

        vector <int> sol(3);
        if (solType == 0) sol = {counts[first] - solDiff, counts[first + 1] + 2 * solDiff, counts[first + 2] - solDiff};
        else sol = {counts[first] + solDiff, counts[first + 1] - 2 * solDiff, counts[first + 2] + solDiff};

        cout<<minCost<<'\n';
        for (int i = 0; i < sol[0]; i++) cout<<first<<" ";
        for (int i = 0; i < sol[1]; i++) cout<<first + 1<<" ";
        for (int i = 0; i < sol[2]; i++) cout<<first + 2<<" ";
    }
    cout<<'\n';

    return 0;
}
