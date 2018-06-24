//greedy (minimum adjacent swaps so that pairs are made adjacent)
//http://codeforces.com/contest/996/problem/D

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solve(vector <int> &a)
{
    int sol = 0;
    while (a.size() > 0)
    {
        int match = find(a.begin(), a.end() - 1, a.back()) - a.begin();
        for (int i = match; i < a.size() - 1; i++)
        {
            swap(a[i], a[i + 1]);
        }
        sol += (a.size() - 1) - match - 1;
        a.pop_back(), a.pop_back();
    }
    return sol;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;
    vector <int> a(2 * n);
    for (int i = 0; i < 2 * n; i++)
    {
        cin>>a[i];
    }

    int sol = solve(a);
    cout<<sol<<'\n';

    return 0;
}
