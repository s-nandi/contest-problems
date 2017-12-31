//dynamic programming (bitmasks, state reduction), subset enumeration
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&page=show_problem&problem=2795
//2010 ICPC World Finals

#include <iostream>
#include <vector>

using namespace std;

bool dp[1 << 15][101];

vector <int> sum;
vector <int> c;
vector <int> pieces;

void print(int &numCase, bool yes)
{
    cout<<"Case "<<numCase<<": ";
    if (yes) cout<<"Yes"<<'\n';
    else cout<<"No"<<'\n';
    numCase++;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T = 1;
    while (true)
    {
        int n;
        cin>>n;
        if (n == 0) break;

        pieces.resize(n);
        sum.resize(1 << n);
        c.resize(1 << n);

        int height, width;
        cin>>height>>width;

        int total = 0;
        for (int i = 0; i < n; i++)
        {
            cin>>pieces[i];
            total += pieces[i];
        }

        if (total != height * width)
        {
            print(T, false);
            continue;
        }

        for (int mask = 0; mask < 1 << n; mask++)
        {
            sum[mask] = 0;
            c[mask] = 0;
            for (int i = 0; i < n; i++)
            {
                if (mask & (1 << i))
                {
                    sum[mask] += pieces[i];
                    c[mask]++;
                }
            }
        }

        for (int mask = 1; mask < 1 << n; mask++)
        {
            for (int h = 1; h <= height; h++)
            {
                dp[mask][h] = false;

                if (sum[mask] % h != 0 or sum[mask] / h > width) continue;

                if (c[mask] == 1)
                {
                    dp[mask][h] = true;
                    continue;
                }

                int w = sum[mask] / h;

                for (int m1 = (mask - 1) % mask; m1 > 0; m1 = (m1 - 1) & mask)
                {
                    int m2 = mask ^ m1;
                    if (m1 < m2) break;

                    if (sum[m1] % w == 0 and sum[m2] % w == 0)
                    {
                        int h1 = sum[m1] / w;
                        int h2 = sum[m2] / w;

                        if (h1 + h2 != h) continue;

                        dp[mask][h] |= dp[m1][h1] & dp[m2][h2];
                    }

                    if (sum[m1] % h == 0 and sum[m2] % h == 0)
                    {
                        int w1 = sum[m1] / h;
                        int w2 = sum[m2] / h;

                        if (w1 + w2 != w) continue;

                        dp[mask][h] |= dp[m1][h] & dp[m2][h];
                    }

                    if(dp[mask][h])
                    {
                        break;
                    }
                }
            }
        }

        print(T, dp[(1 << n) - 1][height]);
    }
    return 0;
}
