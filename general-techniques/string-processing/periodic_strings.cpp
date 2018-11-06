// string processing (substring rotation)
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&page=show_problem&problem=5970
// 2016 Mid-Atlantic Regional

#include <bits/stdc++.h>

using namespace std;

bool solve(const string &s, int k)
{
    for (int i = 0; i + k < s.length(); i += k)
    {
        auto curr = s.substr(i, k), nxt = s.substr(i + k, k);
        rotate(curr.rbegin(), curr.rbegin() + 1, curr.rend());
        if (curr != nxt)
            return false;
    }
    return true;
}

int main()
{
    string s;
    cin >> s;
    int sol = s.length();
    for (int i = 1; i <= s.length(); i++)
    {
        if (s.length() % i != 0) continue;
        if(solve(s, i))
            sol = min(i, sol);
    }
    cout << sol << '\n';
}
