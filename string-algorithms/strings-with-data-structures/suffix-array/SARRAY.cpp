//suffix array (radix sort, inverse SA, space reduction)
//http://www.spoj.com/problems/SARRAY/

#include <iostream>
#include <vector>

using namespace std;

const int alpha = 128;

struct element
{
    pair <int, int> ranking;
    int index;
};

vector <vector <element>> bucket;
void countingSort(vector <element> &v, bool byFirst)
{
    for (int i = 0; i < v.size(); i++)
    {
        bucket[byFirst ? v[i].ranking.first + 1 : v[i].ranking.second + 1].push_back(v[i]);
    }
    for (int i = 0, pos = 0; i < bucket.size(); i++)
    {
        for (auto &elem: bucket[i]) v[pos++] = elem;
        bucket[i].clear();
    }
}

void radixSort(vector <element> &v)
{
    countingSort(v, false);
    countingSort(v, true);
}

struct suffixArray
{
    vector <int> table, inverseTable;
    vector <element> suffix;
    int sz, h = 0, nb;

    suffixArray(string s)
    {
        sz = s.length();
        while (1 << h < sz) h++;
        nb = max(sz, alpha);

        table.resize(sz), suffix.resize(sz), inverseTable.resize(sz);
        bucket.clear(), bucket.resize(nb + 1);

        for (int i = 0; i < sz; i++)
        {
            table[i] = int(s[i]);
        }
        for (int k = 1; k <= h; k++)
        {
            int len = 1 << (k - 1);
            for (int i = 0; i < sz; i++)
            {
                suffix[i] = {{table[i], i + len < sz ? table[i + len] : -1}, i};
            }
            radixSort(suffix);
            for (int i = 0; i < sz; i++)
            {
                table[suffix[i].index] = i > 0 and suffix[i].ranking == suffix[i - 1].ranking ? table[suffix[i - 1].index] : i;
            }
        }
        for (int i = 0; i < sz; i++)
        {
            inverseTable[(*this)[i]] = i;
        }
    }

    int operator [] (int i)
    {
        return table[i];
    }

    int inverse(int i)
    {
        return inverseTable[i];
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin>>s;

    suffixArray sa(s);

    for (int i = 0; i < s.length(); i++)
    {
        cout<<sa.inverse(i)<<'\n';
    }

    return 0;
}
