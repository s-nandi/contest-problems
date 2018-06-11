//dp (knapsack), line sweep
//http://codeforces.com/contest/981/problem/E

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct event
{
    int pos, v;

    bool operator < (const event &o) const
    {
        return pos != o.pos ? pos < o.pos : v > o.v;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin>>n>>q;

    vector <int> possible(n + 1);
    vector <int> dp(n + 1);

    vector <event> events(2 * q);
    for (int i = 0; i < q; i++)
    {
        int l, r, x;
        cin>>l>>r>>x;
        --l, --r;
        events[2 * i] = {l, x};
        events[2 * i + 1] = {r, -x};
    }
    sort(events.begin(), events.end());

    dp[0] = 1;
    for (event e: events)
    {
        if (e.v > 0)
        {
            for (int i = n; i >= e.v; i--)
            {
                dp[i] += dp[i - e.v];
                if (dp[i] > 0)
                    possible[i] = 1;
            }
        }
        else
        {
            int v = -e.v;
            for (int i = v; i <= n; i++)
            {
                dp[i] -= dp[i - v];
            }
        }
    }

    int numPossible = 0;
    for (int i = 0; i <= n; i++)
    {
        if (possible[i])
            numPossible++;
    }

    cout<<numPossible<<'\n';
    for (int i = 0; i <= n; i++)
    {
        if (possible[i])
           cout<<i<<" ";
    }
    cout<<'\n';

    return 0;
}
