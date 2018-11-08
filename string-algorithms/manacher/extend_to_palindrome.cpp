#include <bits/stdc++.h>

using namespace std;

array <vector <int>, 2> manacher(const string &s)
{
    int n = s.length();
    array <vector <int>, 2> pal;
    for (int even = 0; even < 2; even++)
    {
        pal[even].resize(n);
        for (int i = 0, l = 0, r = -1; i < n; i++)
        {
            int k = (i > r) ? !even : min(pal[even][l + r - i + even], r - i + even);
            while (0 <= i - k - even && i + k < n && s[i - k - even] == s[i + k])
                k++;
            pal[even][i] = k--;
            if (i + k > r)
                l = i - k - even, r = i + k;
        }
    }
    return pal;
}

int longestPalindromeEndingAtLast(const string &s)
{
    int len = s.length();
    auto pal = manacher(s);
    int furthestLeft = len - 1;
    for (int even = 0; even < 2; even++)
    {
        for (int i = 0; i < len; i++) if (pal[even][i])
        {
            int l = i - pal[even][i] + !even, r = i + pal[even][i] - 1;
            if (r == len - 1)
                furthestLeft = min(furthestLeft, l);
        }
    }
    return (len - 1) - furthestLeft + 1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string s;
    while (cin >> s)
    {
        int furthestLeft = s.length() - longestPalindromeEndingAtLast(s);
        string sol = s;
        for (int i = furthestLeft - 1; i >= 0; i--)
            sol += s[i];
        cout << sol << '\n';
    }
}
