// dp on digits (hill numbers below threshold)
// https://codeforces.com/gym/100827
// 2014 Pacific Northwest Regional

#include <iostream>
#include <cstring>

using namespace std;

const int MAXL = 70;

bool isHill(string &s)
{
    bool isDown = false;
    for (int i = 1; i < s.length(); i++)
    {
        if (s[i] < s[i - 1])
            isDown = true;
        else if(s[i] > s[i - 1] and isDown)
            return false;
    }
    return true;
}

int main()
{
    int T;
    cin>>T;

    while(T--)
    {
        string s;
        cin>>s;

        if (!isHill(s))
        {
            cout<<-1<<'\n';
            continue;
        }

        // dp[pos][last][stage][below]
        long long dp[MAXL + 5][10][2][2];
        memset(dp, 0, sizeof(dp));

        dp[0][0][0][0] = 1;

        for (int i = 0; i < s.length(); i++)
        {
            int threshold = s[i] - '0';
            for (int old = 0; old < 10; old++)
            {
                for (int dig = 0; dig < 10; dig++)
                {
                    for (int stage = 0; stage < 2; stage++)
                    {
                        for (int below = 0; below < 2; below++)
                        {
                            if (below == 0 and dig > threshold)
                                continue;
                            if (stage == 1 and dig > old)
                                continue;

                            dp[i + 1][dig][stage or dig < old][below or dig < threshold] += dp[i][old][stage][below];
                        }
                    }
                }
            }
        }
        long long sol = 0;
        for (int dig = 0; dig < 10; dig++)
        {
            for (int stage = 0; stage < 2; stage++)
            {
                sol += dp[s.length()][dig][stage][1];
            }
        }
        cout<<sol<<'\n';
    }
}
