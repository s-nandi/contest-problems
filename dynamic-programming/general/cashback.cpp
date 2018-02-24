//dynamic programming, optimal partitioning when ignoring 1 element, sliding window
//http://codeforces.com/problemset/problem/940/E

#include <iostream>
#include <vector>
#include <set>

using namespace std;

#define ll long long

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, c;
    cin>>n>>c;

    vector <int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
    }

    multiset <int> current;
    vector <ll> excluded(n);

    ll acc = 0;
    for (int i = 0; i < n; i++)
    {
        acc += a[i];
        current.insert(a[i]);

        excluded[i] = acc;
        if (i >= c - 1)
        {
            excluded[i] -= *current.begin();
            acc -= a[i - c + 1];
            current.erase(current.find(a[i - c + 1]));
        }
    }

    ll dp[n + 1];
    dp[0] = 0;

    for (int i = 0; i < n; i++)
    {
        dp[i + 1] = dp[i] + a[i];
        if (i + 1 >= c)
        {
            dp[i + 1] = min(dp[i + 1], excluded[i] + dp[i + 1 - c]);
        }
    }

    cout<<dp[n]<<'\n';

    return 0;
}
