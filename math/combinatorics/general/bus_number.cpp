//combinatorics (combinations with repeated elements), combinations generator
//http://codeforces.com/contest/991/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXD = 19;

vector <ll> factorial;
void precompute(int n)
{
    factorial.resize(n + 1);
    factorial[0] = 1;
    for (int i = 1; i <= n; i++)
        factorial[i] = factorial[i - 1] * i;
}

map <int, int> original;
ll numArrangements(map <int, int> &digits, bool checkLeading = true)
{
    if (digits.size() < original.size())
        return 0;

    int dig = 0;
    ll denom = 1;
    for (auto elem: digits)
    {
        dig += elem.second;
        denom *= factorial[elem.second];
    }
    auto res = factorial[dig] / denom;
    if (checkLeading and digits.count(0))
    {
        digits[0]--;
        res -= numArrangements(digits, false);
        digits[0]++;
    }
    return res;
}

ll combinations(map <int, int> &digits, int prev = -1)
{
    ll acc = numArrangements(digits);
    for (auto &elem: original)
    {
        digits[elem.first]++;

        if (digits[elem.first] <= elem.second and elem.first >= prev)
            acc += combinations(digits, elem.first);

        if (--digits[elem.first] == 0)
            digits.erase(elem.first);
    }
    return acc;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute(MAXD);

    string s;
    cin >> s;

    for (char c: s)
        original[c - '0']++;

    map <int, int> digits;
    cout << combinations(digits) << '\n';
}
