//suffix array (string rotation)
//https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&page=show_problem&problem=756
//2003 Southeastern European Regional

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int alpha = 26;

struct element
{
    pair <int, int> ranking;
    int index;
    bool operator < (element o) const
    {
        return ranking != o.ranking ? ranking < o.ranking : index < o.index;
    }
};

vector <vector <element>> bucket;
void countingSort(vector <element> &v, bool byFirst)
{
    for (int i = 0; i < v.size(); i++)
    {
        bucket[byFirst ? v[i].ranking.first : v[i].ranking.second].push_back(v[i]);
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
    vector <vector<int>> table;
    vector <element> suffix;
    int sz, h = 0, nb;

    suffixArray(string s)
    {
        sz = s.length();
        while (1 << h < sz) h++;
        nb = max(sz, alpha);

        table.resize(sz, vector<int>(h + 1)), suffix.resize(sz), bucket.resize(nb);

        for (int i = 0; i < sz; i++)
        {
            table[i][0] = s[i] - 'a';
        }
        for (int k = 1; k <= h; k++)
        {
            int len = 1 << (k - 1);
            for (int i = 0; i < sz; i++)
            {
                suffix[i] = {{table[i][k - 1], table[(i + len) % sz][k - 1]}, i};
            }
            radixSort(suffix);
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
