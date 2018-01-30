#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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

        table.resize(sz, vector<int>(h + 1)), suffix.resize(sz);

        for (int i = 0; i < sz; i++)
        {
            table[i][0] = s[i] - 'a';
        }
        for (int k = 1, len = 1; k <= h; k++, len <<= 1)
        {
            for (int i = 0; i < sz; i++)
            {
                suffix[i] = {{table[i][k - 1], table[(i + len) % sz][k - 1]}, i};
            }
            sort(suffix.begin(), suffix.end());
            for (int i = 0; i < sz; i++)
            {
                table[suffix[i].index][k] = i > 0 and suffix[i].ranking == suffix[i - 1].ranking ? table[suffix[i - 1].index][k] : i;
            }
        }
    }

    int minSuffix()
    {
        return suffix[0].index;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin>>T;

    while(T--)
    {
        int sz;
        cin>>sz;

        string s;
        cin>>s;

        suffixArray sa = suffixArray(s);

        cout<<sa.minSuffix()<<endl;
    }

    return 0;
}
