// string parsing (trim last instances of character)
// https://open.kattis.com/problems/orphanbackups
// 2018 Mid-Atlantic Regional

#include <bits/stdc++.h>

using namespace std;

string trimLast(const string &s, char c, int n = 1)
{
    int pos = s.length();
    for (int i = 0; i < n; i++)
    {
        auto idx = s.find_last_of(c, pos - 1);
        if (idx == string::npos)
            break;
        pos = idx;
    }
    return string(s.begin(), s.begin() + pos);
}

template <typename T>
struct indexing
{
    map <T, int> mapping;
    int getIndex(const T &elem)
    {
        if (mapping.count(elem))
            return mapping[elem];
        else
        {
            int idx = mapping.size();
            mapping[elem] = idx;
            return idx;
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string line;
    int phase = 0;
    map <int, vector<string>> indexed[2];
    indexing <string> ind;
    while (getline(cin, line))
    {
        if (line.empty())
            phase++;
        else
        {
            string key = phase == 0 ? line : trimLast(line, '_', 2);
            int index = ind.getIndex(key);
            indexed[phase][index].push_back({line});
        }
    }

    string outChar[2] = {"I", "F"};
    vector <string> output;
    for (int t = 1; t >= 0; t--)
    {
        for (auto &elem: indexed[t])
        {
            if (!indexed[1 - t].count(elem.first))
            {
                for (auto &s: elem.second)
                    output.push_back(outChar[t] + " " + s);
            }
        }
    }
    sort(output.begin(), output.end());

    if (!output.empty())
    {
        for (auto &res: output)
            cout << res << '\n';
    }
    else
        cout << "No mismatches." << '\n';
}
