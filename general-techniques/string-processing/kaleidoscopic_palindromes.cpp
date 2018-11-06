// string processing (converting binary string to integer, converting integer to base-b string), backtracking (generating length-l palindromic binary strings)
// https://open.kattis.com/problems/kaleidoscopicpalindromes
// 2018 North Central NA Regional

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef basic_string<int> istring;

template <class T> bool isPalindrome(const T &s)
{
    return s == istring(s.rbegin(), s.rend());
}

bool isPalindrome(ll val, int base)
{
    istring digs;
    while (val)
    {
        digs.push_back(val % base);
        val /= base;
    }
    return isPalindrome(digs);
}

ll getValue(const istring &s, int base)
{
    ll pos = 1, res = 0;
    for (int i = s.length() - 1; i >= 0; i--)
    {
        res += s[i] * pos;
        pos *= base;
    }
    return res;
}

void generatePalindromes(istring &s, vector <istring> &palindrome, int minDigit, int maxDigit, int len)
{
    if (2 * s.length() > len) assert(false);
    else if (2 * s.length() == len)
    {
        istring rev(s.rbegin(), s.rend());
        palindrome.push_back(s + rev);
    }
    else if(2 * s.length() + 1 == len)
    {
        istring rev(s.rbegin(), s.rend());
        for (int i = minDigit; i <= maxDigit; i++)
            palindrome.push_back(s + i + rev);
    }
    else
    {
        for (int i = minDigit; i <= maxDigit; i++) if (!s.empty() or i > 0)  // PS: if-condition ensures no leading-zeros
        {
            s += i;
            generatePalindromes(s, palindrome, minDigit, maxDigit, len);
            s.pop_back();
        }
    }
}

vector <istring> findPalindromes(int len, int minDigit, int maxDigit)
{
    vector <istring> res;
    istring init;
    generatePalindromes(init, res, minDigit, maxDigit, len);
    return res;
}

int solve(int a, int b, int k)
{
    int res = 0;
    for (int dig = 1, done = false; !done; dig++)
    {
        for (const auto &s: findPalindromes(dig, 0, 1))
        {
            auto val = getValue(s, 2);

            if (val < a)
                continue;
            else if (val > b)
            {
                done = true;
                break;
            }
            else
            {
                bool valid = true;
                for (int base = 2; base <= k; base++) if (!isPalindrome(val, base))
                {
                    valid = false;
                    break;
                }
                res += valid;
            }
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int a, b, k;
    cin >> a >> b >> k;

    cout << solve(a, b, k) << '\n';
}
