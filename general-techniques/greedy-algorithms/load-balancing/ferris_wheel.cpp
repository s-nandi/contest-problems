//greedy (load balancing)
//https://cses.fi/problemset/task/1090/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    cin>>n>>x;

    vector <int> w(n);

    for (int i = 0; i < n; i++)
    {
        cin>>w[i];
    }
    sort(w.begin(), w.end());

    int l = 0, r = n - 1, sol = 0;
    while (l <= r)
    {
        while (l < r and w[l] + w[r] > x)
        {
            r--;
            sol++;
        }

        sol++, l++, r--;
    }

    cout<<sol<<'\n';

    return 0;
}
