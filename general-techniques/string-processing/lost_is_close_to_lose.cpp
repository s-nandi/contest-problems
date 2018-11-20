// string parsing (splitting, remove non-alphabetical characters / convert upper-case to lower-case)
// https://open.kattis.com/problems/lostisclosetolose
// 2018 Mid-Atlantic Regional

#include <bits/stdc++.h>

using namespace std;

vector <string> split(const string &s, const string delims = " ")
{
    bool isNew = true;
    vector <string> res;
    for (int i = 0; i < s.length(); i++)
    {
        bool isDelim = false;
        for (char c: delims)
        {
            if (s[i] == c)
                isDelim = isNew = true;
        }
        if (!isDelim)
        {
            if (isNew)
                res.push_back("");
            res.back() += s[i];
            isNew = false;
        }
    }
    return res;
}

string getCore(const string &s)
{
    string res(s);
    transform(res.begin(), res.end(), res.begin(), [](char c){return tolower(c);});
    res.erase(remove_if(res.begin(), res.end(), [](char c){return !isalpha(c);}), res.end());
    return res;
}

bool canDelete(const string &a, const string &b)
{
    if (a.length() - 1 == b.length())
    {
        for (int i = 0; i < a.length(); i++)
        {
            string c(a);
            c.erase(c.begin() + i);
            if (c == b)
                return true;
        }
    }
    return false;
}

bool canReplace(const string &a, const string &b)
{
    if (a.length() == b.length())
    {
        int diff = 0;
        for (int i = 0; i < a.length(); i++)
            diff += a[i] != b[i];
        if (diff == 1)
            return true;
    }
    return false;
}

bool canSwap(const string &a, const string &b)
{
    if (a.length() == b.length())
    {
        for (int i = 0; i + 1 < a.length(); i++)
        {
            string c(a);
            swap(c[i], c[i + 1]);
            if (c == b)
                return true;
        }
    }
    return false;
}

bool canTransform(const string &a, const string &b)
{
    return canDelete(a, b) or canDelete(b, a) or canReplace(a, b) or canSwap(a, b);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string line;
    vector <string> cores;
    while (getline(cin, line))
    {
        if (line == "***")
            break;
        for (auto &s: split(line))
            cores.push_back(getCore(s));
    }
    sort(cores.begin(), cores.end());
    cores.erase(unique(cores.begin(), cores.end()), cores.end());
    cores.erase(remove_if(cores.begin(), cores.end(), [](const string &s){return s.empty();}), cores.end());

    vector <vector<int>> transformable(cores.size());
    for (int i = 0; i < cores.size(); i++)
    {
        for (int j = 0; j < cores.size(); j++) if (i != j)
        {
            if (canTransform(cores[i], cores[j]))
                transformable[i].push_back(j);
        }
    }

    bool printed = false;
    for (int i = 0; i < cores.size(); i++) if (!transformable[i].empty())
    {
        cout << cores[i] << ": ";
        for (auto j: transformable[i])
            cout << cores[j] << " ";
        cout << '\n';
        printed = true;
    }
    if (!printed)
        cout << "***" << '\n';
}
