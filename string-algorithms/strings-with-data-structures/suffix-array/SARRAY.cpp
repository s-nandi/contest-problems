//suffix array
//http://www.spoj.com/problems/SARRAY/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int mapping(char c)
{
    return int(c);
}

struct element
{
    pair <int, int> ranking;
    int index;
    bool operator < (element o) const
    {
        return ranking != o.ranking ? ranking < o.ranking : index < o.index;
    }
};

struct suffixArray
{
    vector <vector<int>> table;
    vector <element> suffix;
    int sz, h = 0;

    suffixArray(string s)
    {
        sz = s.length();
        while (1 << h < sz) h++;

        table.resize(sz, vector<int>(h + 1));
        suffix.resize(sz);

        for (int i = 0; i < sz; i++)
        {
            table[i][0] = mapping(s[i]);
        }
        for (int k = 1; k <= h; k++)
        {
            int len = 1 << (k - 1);
            for (int i = 0; i < sz; i++)
            {
                suffix[i] = {{table[i][k - 1], i + len < sz ? table[i + len][k - 1] : -1}, i};
            }
            sort(suffix.begin(), suffix.end());

            for (int i = 0; i < sz; i++)
            {
                table[suffix[i].index][k] = i > 0 and suffix[i].ranking == suffix[i - 1].ranking ? table[suffix[i - 1].index][k] : i;
            }
        }
    }

    int operator [] (int i)
    {
        return table[i][h];
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin>>s;

    suffixArray sa(s);
    vector <int> solution(s.length());

    for (int i = 0; i < s.length(); i++)
    {
        solution[sa[i]] = i;
    }
    for (int i: solution)
    {
        cout<<i<<'\n';
    }

    return 0;
}
