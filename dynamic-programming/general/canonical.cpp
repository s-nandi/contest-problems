// dp (coin change, checking if greedy algorithm is optimal for set of coins)
// https://open.kattis.com/problems/canonical
// 2017 North American Qualifier

#include <bits/stdc++.h>

using namespace std;

const int INF = 1231231234;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector <int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    int mv = a[n - 2] + a[n - 1];

    vector <int> dp(mv + 1, INF);
    dp[0] = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < mv; j++)
        {
            if (j + a[i] <= mv)
            {
                dp[j + a[i]] = min(dp[j + a[i]], dp[j] + 1);
                if (dp[j + a[i]] == -1)
                    dp[j + a[i]] = dp[j] + 1;
            }
        }
    }

    vector <int> greedy(mv + 1, 0);
    bool diff = false;
    for (int j = mv; j >= 1; j--)
    {
        int rem = j;
        for (int i = n - 1; i >= 0; i--) if (a[i] <= rem)
        {
            greedy[j] += rem / a[i];
            rem %= a[i];
        }

        if (greedy[j] != dp[j])
        {
            diff = true;
            break;
        }
    }

    if (diff)
        cout<<"non-canonical"<<'\n';
    else
        cout<<"canonical"<<'\n';
}
