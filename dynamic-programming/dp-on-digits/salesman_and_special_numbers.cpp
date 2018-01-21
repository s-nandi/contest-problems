//dp on digits, bitmasks
//http://codeforces.com/contest/914/problem/C

#include <iostream>
#include <cstring>

using namespace std;

#define ll long long
#define MOD 1000000007

int numBits(int n)
{
    int counter = 0;
    while (n > 0)
    {
        if (n & 1) counter++;
        n >>= 1;
    }
    return counter;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string n;
    int k;
    cin>>n>>k;

    int len = n.length();

    if (k == 0)
    {
        cout<<1<<'\n';
        return 0;
    }

    int dp[1 << 10];
    memset(dp, 0, sizeof(dp));

    for (int i = 2; i < (1 << 10); i++)
    {
        int nb = numBits(i);
        dp[i] = dp[nb] + 1;
    }

    int dp2[2][len][1001];
    memset(dp2, 0, sizeof(dp2));

    dp2[1][0][0] = 1;
    dp2[0][0][1] = 1;

    for (int i = 1; i < n.length(); i++)
    {
        for (int numBits = 0; numBits <= 1000; numBits++)
        {
            if (n[i] == '1')
            {
                dp2[1][i][numBits] = dp2[0][i - 1][numBits] + dp2[1][i - 1][numBits];
                dp2[1][i][numBits] %= MOD;
                if (numBits > 0)
                {
                    dp2[1][i][numBits] += dp2[1][i - 1][numBits - 1];
                    dp2[1][i][numBits] %= MOD;
                    dp2[0][i][numBits] = dp2[0][i - 1][numBits - 1];
                }
            }
            else
            {
                dp2[1][i][numBits] = dp2[1][i - 1][numBits];
                dp2[0][i][numBits] = dp2[0][i - 1][numBits];
                if (numBits > 0)
                {
                    dp2[1][i][numBits] += dp2[1][i - 1][numBits - 1];
                    dp2[1][i][numBits] %= MOD;
                }
            }
        }
    }
    dp2[1][len - 1][1]--; //1 is edge case

    int sol = 0;
    for (int numBits = 1; numBits <= 1000; numBits++)
    {
        if (dp[numBits] == k - 1)
        {
            sol += dp2[0][len - 1][numBits] + dp2[1][len - 1][numBits];
            sol %= MOD;
        }
    }

    cout<<sol<<'\n';

    return 0;
}
