// DP to find maximum number of partitions with different cost for binary search branches
// https://codeforces.com/gym/100820
// 2015 Pacific Northwest Regional
// Solution from: http://serjudging.vanb.org/wp-content/uploads/weightlifting_vanb.java

#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

const double EPS = .00000001;

int main()
{
    int E, E_success, E_fail;
    cin>>E>>E_success>>E_fail;

    int dp[E + 1];
    memset(dp, 0, sizeof(dp));

    cout<<setprecision(6)<<fixed;

    for (int i = 1; i <= E; i++)
    {
        if (i >= E_fail)
        {
            dp[i] += dp[i - E_fail];
        }
        if (i >= E_success)
        {
            dp[i] += dp[i - E_success];
        }
        dp[i]++;
        if (225.0 / (dp[i] + 1) < EPS or 200.0 / (dp[i]) < EPS)
        {
            cout<<0.000000<<'\n';
            return 0;
        }
    }
    cout<<min(200.0 / dp[E], 225.0 / (dp[E] + 1))<<'\n';

    return 0;
}
