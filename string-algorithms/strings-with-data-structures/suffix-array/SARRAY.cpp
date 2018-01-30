//suffix array (radix sort, inverse SA, space reduction)
//http://www.spoj.com/problems/SARRAY/

#include <iostream>
#include <vector>

using namespace std;

#define MAXN 100001

struct element
{
    pair <int, int> ranking;
    int index;
};

vector <element> bucket[MAXN];
int numBuckets;
void countingSort(vector <element> &v, bool byFirst)
{
    for (int i = 0; i < v.size(); i++)
    {
        bucket[byFirst ? v[i].ranking.first + 1 : v[i].ranking.second + 1].push_back(v[i]);
    }
    for (int i = 0, pos = 0; i <= numBuckets; i++)
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
    vector <int> ranks, ordered;
    vector <element> suffix;
    int sz, h = 0;

    suffixArray(string s)
    {
        sz = s.length();
        while (1 << h < sz) h++;

        ranks.resize(sz), suffix.resize(sz), ordered.resize(sz);

        numBuckets = 0;
        for (int i = 0; i < sz; i++)
        {
            ranks[i] = int(s[i]);
            numBuckets = max(numBuckets, ranks[i] + 1);
        }
        for (int k = 1, len = 1; k <= h; k++, len <<= 1)
        {
            for (int i = 0; i < sz; i++)
            {
                suffix[i] = {{ranks[i], i + len < sz ? ranks[i + len] : -1}, i};
            }
            radixSort(suffix);
            numBuckets = 0;
            for (int i = 0; i < sz; i++)
            {
                ranks[suffix[i].index] = i > 0 and suffix[i].ranking == suffix[i - 1].ranking ? ranks[suffix[i - 1].index] : numBuckets++;
            }
            if (numBuckets == sz) break;
        }
        for (int i = 0; i < sz; i++)
        {
            ordered[ranks[i]] = i;
        }
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
        cout<<sa.ordered[i]<<'\n';
    }

    return 0;
}
