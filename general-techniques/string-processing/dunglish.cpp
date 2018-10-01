// ad-hoc (dictionary of strings, basic counting)
// http://codeforces.com/gym/101623/attachments (problem D)
// 2017 Northwest European Regional

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const string CORRECT = "correct";
const string INCORRECT = "incorrect";

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector <string> sentence(n);
    for (int i = 0; i < n; i++)
    {
        cin >> sentence[i];
    }

    int m;
    cin >> m;

    map <string, int> validDict, totalDict;
    map <string, string> translate;
    for (int i = 0; i < m; i++)
    {
        string from, to, type;
        cin >> from >> to >> type;

        totalDict[from]++;
        translate[from] = to;
        if (type == CORRECT)
            validDict[from]++;
    }

    ll total = 1, valid = 1;
    string translation = "";
    for (const string &s: sentence)
    {
        translation += translate[s] + " ";
        total *= totalDict[s];
        valid *= validDict[s];
    }
    translation.pop_back();
    if (total == 1)
    {
        cout << translation << '\n';
        string res = valid == 1 ? CORRECT : INCORRECT;
        cout << res << '\n';
    }
    else
    {
        cout << valid << " " << CORRECT << '\n';
        cout << (total - valid) << " " << INCORRECT << '\n';
    }
}
