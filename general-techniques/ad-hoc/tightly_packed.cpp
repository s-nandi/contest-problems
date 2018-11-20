// ad-hoc (math)
// https://open.kattis.com/problems/tightlypacked
// 2018 Mid-Atlantic Regional

#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long n;
    cin >> n;

    auto best = n;
    for (long long i = 1; i * i <= n; i++)
    {
        for (long long j = n / i - 3; j <= n / i + 3; j++)
        {
            if (2 * j >= i and j <= 2 * i and i * j >= n)
                best = min(best, i * j - n);
        }
    }
    cout << best << '\n';
}
