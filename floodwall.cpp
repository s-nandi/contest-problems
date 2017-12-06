#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define ll long long
#define INF 123123123123123

struct interval
{
    ll left;
    ll right;

    bool operator < (interval o) const
    {
        return right < o.right or (right == o.right and left < o.left);
    }
};

int main()
{
    int n;

    while(cin >> n)
    {
        vector <interval> paintings(n);
        for (int i = 0; i  < n; i++)
        {
            ll l, r;
            cin>>l>>r;
            paintings[i] = {l, r};
        }
        sort(paintings.begin(), paintings.end());

        vector <ll> dp(n + 1);
        dp[0] = 0;
        for (int i = 0; i < n; i++)
        {
            interval invl = {0, paintings[i].left + 1};
            int pos = lower_bound(paintings.begin(), paintings.end(), invl) - paintings.begin() - 1;

            dp[i + 1] = max(dp[i], dp[pos + 1] + paintings[i].right - paintings[i].left);
        }
        cout<<dp[n]<<'\n';
    }
}
